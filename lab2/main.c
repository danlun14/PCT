#include <stdio.h>
#include <stdlib.h>
#include "hpctimer.h"
#include <omp.h>

enum
{
	N = 40000,
	NREPS = 3
};

void printVector(double *v, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%.3lf ", v[i]);
	}
	printf("\n");
}

int main()
{

	int m = N, n = N;
	int numt = 0;
	scanf("%d", &numt);
	double *a, *b, *c;
	// Allocate memory for 2-d array a[m, n]
	a = malloc(sizeof(*a) * m * n);
	b = malloc(sizeof(*b) * n);
	c = malloc(sizeof(*c) * m);
	/*#pragma omp parallel num_threads(6)
	{
		int nthreads = omp_get_num_threads();
		int threadid = omp_get_thread_num();
		int items_per_thread = m / nthreads;
		int lb = threadid * items_per_thread;
		int ub = (threadid == nthreads - 1) ? (m - 1) : (lb + items_per_thread - 1);
		for (int i = lb; i <= ub; i++)
		{
			for (int j = 0; j < n; j++)
				a[i * n + j] = i + j;
			c[i] = 0.0;
		}
#pragma omp barrier
	}*/
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			a[i * n + j] = i + j;
		c[i] = 0.0;
	}
	for (int j = 0; j < n; j++)
	{
		b[j] = j;
	}

	printf("\nN = %d\n", N);
	double t = hpctimer_getwtime();
	for (int i = 0; i < NREPS; i++)
	{
		for (int i = 0; i < N; i++)
		{
			c[i] = 0.0;
			for (int j = 0; j < n; j++)
				c[i] += a[i * n + j] * b[j];
		}
	}
	t = hpctimer_getwtime() - t;
	t = t / NREPS;
	printf("Elapsed time non parallel: %.6f sec.\n", t);
	double t1 = omp_get_wtime();
	for (int i = 0; i < NREPS; i++)
	{

#pragma omp parallel num_threads(numt)
		{
#pragma omp master
			printf("Num Threads = %d\n", omp_get_num_threads());

			int nthreads = omp_get_num_threads();
			int threadid = omp_get_thread_num();
			int items_per_thread = N / nthreads;
			int lb = threadid * items_per_thread;
			int ub = (threadid == nthreads - 1) ? (m - 1) : (lb + items_per_thread - 1);
			for (int i = lb; i <= ub; i++)
			{
				c[i] = 0.0;
				for (int j = 0; j < n; j++)
					c[i] += a[i * n + j] * b[j];
			}

#pragma omp barrier
		}
	}
	t1 = omp_get_wtime() - t1;
	t1 = t1 / NREPS;

	printf("Elapsed time: %.6f sec.\n", t1);
	printf("Speedup = %.4lf\n", t / t1);
	return 0;
}
