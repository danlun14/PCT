#define _POSIX_C_SOURCE 1
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define eps 1E-5

double f_x(double x)
{
    return (x / pow(sin(2 * x), 3));
}

void Runge(int numt, double *start_time)
{
    double t = omp_get_wtime();
    double a = 0.1;
    double b = 0.5;
    int n0 = 100000000;

    printf("Numerical integration: [%f, %f], n0 = %d, EPS = %f\n", a, b, n0, eps);

    double sq[2];

#pragma omp parallel num_threads(numt)
    {
#pragma omp master
        printf("num threads = %d\n", omp_get_num_threads());
        int n = n0;
        int k;
        double delta = 1;

        for (k = 0; delta > eps; n *= 2, k ^= 1)
        {
            double sloc = 0.0;
            double h = (b - a) / n;

            sq[k] = 0.0;
#pragma omp barrier

#pragma omp for nowait
            for (int i = 0; i < n; i++)
            {
                sloc += f_x(a + h * (i + 0.5));
            }

#pragma omp atomic
            sq[k] += sloc * h;

#pragma omp barrier
            if (n > n0)
            {
                delta = fabs(sq[k] - sq[k ^ 1]) / 3.0;
            }
        }

#pragma omp master
        printf("Result: %.12f; Runge rule: EPS %e, n %d\n", sq[k], eps, n / 2);
    }

    t = omp_get_wtime() - t;
    printf("Elapsed time (sec.): %.6f\n\n", t);
    if (numt == 1)
    {
        *start_time = t;
    }
    double speedup = 0;
    speedup = *start_time / t;
    FILE *results = fopen("RecInt", "a");
    fprintf(results, "%d %.6f\n", numt, speedup);
}

double getrand(unsigned int *seed)
{
    return (double)rand_r(seed) / RAND_MAX;
}

double f_xy(double x, double y)
{
    return (exp(pow(x + y, 2)));
}

void Monte_Carlo(int numt, double *start_time)
{
    double t = omp_get_wtime();
    int n = 1E7;

    int in = 0;
    double s = 0;

#pragma omp parallel num_threads(numt)
    {
#pragma omp master
        printf("num threads = %d\n", omp_get_num_threads());
        double s_loc = 0.0;
        int in_loc = 0;
        unsigned int seed = omp_get_thread_num();

#pragma omp for nowait
        for (int i = 0; i < n; i++)
        {
            double x = getrand(&seed);
            double y = getrand(&seed) - x;
            if (1 - x >= y) //?
            {
                in_loc++;
                s_loc += f_xy(x, y);
            }
        }
#pragma omp atomic
        s += s_loc;
#pragma omp atomic
        in += in_loc;
    }

    double v = in / n;
    double res = (v * s) / in;

    t = omp_get_wtime() - t;

    printf("Result: %.12f, n %d \n", res, n);
    printf("Elapsed time = %lf\n\n", t);
    if (numt == 1)
    {
        *start_time = t;
    }
    double speedup = 0;
    speedup = *start_time / t;
    if (n == 1E7)
    {
        FILE *results = fopen("MC_n1E7", "a");
        fprintf(results, "%d %.6f\n", numt, speedup);
    }
    else if (n == 1E8)
    {
        FILE *results = fopen("MC_n1E8", "a");
        fprintf(results, "%d %.6f\n", numt, speedup);
    }
}

int main()
{
    double st = 0;
    int numt[4] = {1, 2, 4, 6};
    for (int i = 0; i < 4; i++)
    {
        Runge(numt[i], &st);
        //Monte_Carlo(numt[i], &st);
    }

    return 0;
}