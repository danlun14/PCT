/*
 * loop.c:
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hpctimer.h"

enum
{
    n = 512 * 1024 * 1024
};

int main()
{
    int *v, i, sum, t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0, t6 = 0, t7 = 0, t8 = 0, nThreads;
    double t;
    if ((v = malloc(sizeof(*v) * n)) == NULL)
    {
        fprintf(stderr, "No enough memory\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < n; i += 1)
    {
        v[i] = 1;
    }
    t = hpctimer_wtime();
    for (sum = 0, i = 0; i < n; i += 1)
    {
        sum += v[i];
    }
    t = hpctimer_wtime() - t;

    printf("Sum = %d\n", sum);
    printf("Elapsed time (sec.): %.6f\n", t);
    t = hpctimer_wtime();
    /* TODO: Unroll this loop */
    for (sum = 0, i = 0; i < n; i += 4)
    {
        t1 += v[i];
        t2 += v[i + 1];
        t3 += v[i + 2];
        t4 += v[i + 3];
        /*t5 += v[i + 4];
        t6 += v[i + 5];
        t7 += v[i + 6];
        t8 += v[i + 7];*/
    }
    t = hpctimer_wtime() - t;
    sum = t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8;
    printf("Sum = %d\n", sum);
    printf("Elapsed time (sec.): %.6f\n", t);

    free(v);
    return 0;
}
