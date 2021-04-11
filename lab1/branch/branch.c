/*
 * branch.c:
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hpctimer.h"

enum
{
    n = 1000000,
    NREPS = 10
};

double x[n], y[n], z[n];

int map_init()
{
    for (int i = 0; i < n; i++)
    {

        y[i] = rand() % 6000;
    }

    for (int i = 0; i < n; i++)
    {
        x[i] = rand() % 6000;
    }
    return 0;
}

void blend_map(double *dest, double *a, double *b, int size, int blend)
{
    int i = 0;

    for (i = 0; i < size; i++)
    {
        if (blend == 255)
        {
            dest[i] = a[i];
        }
        else if (blend == 0)
        {
            dest[i] = b[i];
        }
        else
        {
            dest[i] = a[i] * blend + b[i] * (255 - blend) / 256.0;
        }
    }
}

void blend_map_opt(double *dest, double *a, double *b, int size, int blend)
{
    int i = 0;

    if (blend == 255)
    {
        for (i = 0; i < size; i++)
        {
            dest[i] = a[i];
        }
        return;
    }
    if (blend == 0)
    {
        for (i = 0; i < size; i++)
        {
            dest[i] = b[i];
        }
        return;
    }
    for (i = 0; i < size; i++)
    {
        dest[i] = a[i] * blend + b[i] * (255 - blend) / 256.0;
    }
}

int main()
{
    double t_start, t;
    int i;

    map_init();

    t_start = hpctimer_wtime();
    blend_map_opt(z, x, y, n, 0);
    t_start = hpctimer_wtime() - t_start;

    t = hpctimer_wtime();
    for (i = 0; i < NREPS; i++)
    {
        blend_map_opt(z, x, y, n, 1);
    }
    t = (hpctimer_wtime() - t) / NREPS;

    printf("First run (sec.): %.6f\n", t_start);
    printf("Mean of %d runs (sec.): %.6f\n", NREPS, t);
    /*
    t = hpctimer_wtime();
    for (i = 0; i < NREPS; i++)
    {
        blend_map_opt(z, x, y, n, 1);
    }
    t = (hpctimer_wtime() - t) / NREPS;
    printf("Mean of %d runs opt(sec.): %.6f\n", NREPS, t);
*/
    return 0;
}
