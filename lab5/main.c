#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>

// #define N 10000000
#define THRESHOLD 1000

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void partition(int *array, int *i, int *j, int low, int high)
{
	*i = low;
	*j = high;
	int pivot = array[(low + high) / 2];
	do
	{
		while (array[*i] < pivot)
			(*i)++;
		while (array[*j] > pivot)
			(*j)--;
		if ((*i) <= (*j))
		{
			swap(&array[*i], &array[*j]);
			(*i)++;
			(*j)--;
		}
	} while ((*i) <= (*j));
}

void quicksort(int *array, int low, int high, int THRESHOLD1)
{
	int i = 0;
	int j = 0;

	partition(array, &i, &j, low, high);

	if (high - low < THRESHOLD1 || j - low < THRESHOLD1 || high - i < THRESHOLD1)
	{
		if (low < j)
		{
			quicksort(array, low, j, THRESHOLD1);
		}
		if (i < high)
		{
			quicksort(array, i, high, THRESHOLD1);
		}
	}
	else
	{
#pragma omp task untied
		{
			quicksort(array, low, j, THRESHOLD1);
		}
		quicksort(array, i, high, THRESHOLD1);
	}
}

void quicksort_ser(int *array, int low, int high)
{
	int i = 0;
	int j = 0;

	partition(array, &i, &j, low, high);

	if (low < j)
	{
		quicksort_ser(array, low, j);
	}
	if (i < high)
	{
		quicksort_ser(array, i, high);
	}
}

void init_array(int *array, int N)
{
	for (int i = 0; i < N; i++)
	{
		array[i] = rand() / (RAND_MAX + 1.0) * (100000 - 1) + 1;
		;
	}
}

int main()
{
	int N[5] = {10000, 100000, 1000000, 10000000, 100000000};
	int Tr[4] = {10, 100, 1000, 10000};
	int nthreads[3] = {2, 4, 6};
	/*FILE *f10_10000 = fopen("threashold10_10000", "w");
	FILE *f10_100000 = fopen("threashold10_100000", "w");
	FILE *f10_1000000 = fopen("threashold10_1000000", "w");
	FILE *f10_10000000 = fopen("threashold10_10000000", "w");
	FILE *f10_100000000 = fopen("threashold10_100000000", "w");

	FILE *f100_10000 = fopen("threashold100_10000", "w");
	FILE *f100_100000 = fopen("threashold100_100000", "w");
	FILE *f100_1000000 = fopen("threashold100_1000000", "w");
	FILE *f100_10000000 = fopen("threashold100_10000000", "w");
	FILE *f100_100000000 = fopen("threashold100_100000000", "w");

	FILE *f1000_10000 = fopen("threashold1000_10000", "w");
	FILE *f1000_100000 = fopen("threashold1000_100000", "w");
	FILE *f1000_1000000 = fopen("threashold1000_1000000", "w");
	FILE *f1000_10000000 = fopen("threashold1000_10000000", "w");
	FILE *f1000_100000000 = fopen("threashold1000_100000000", "w");

	FILE *f10000_10000 = fopen("threashold10000_10000", "w");
	FILE *f10000_100000 = fopen("threashold10000_100000", "w");
	FILE *f10000_1000000 = fopen("threashold10000_1000000", "w");
	FILE *f10000_10000000 = fopen("threashold10_00010000000", "w");
	FILE *f10000_100000000 = fopen("threashold10000_100000000", "w");*/
	for (int m = 0; m < 4; m++)
	{
		printf("******************%d****************\n", Tr[m]);
		for (int j = 0; j < 5; j++)
		{
			printf("N = %d\n", N[j]);

			int *orig_arr = malloc(sizeof(int) * N[j]);
			int *for_test_arr = malloc(sizeof(int) * N[j]);

			init_array(orig_arr, N[j]);
			memcpy(for_test_arr, orig_arr, sizeof(int) * N[j]);
			double t_ser = omp_get_wtime();

			quicksort_ser(for_test_arr, 0, N[j] - 1);
			t_ser = omp_get_wtime() - t_ser;
			printf("Time serial = %.5lf\n", t_ser);
			printf("1 1\n");
			for (int i = 0; i < 3; i++)
			{
				memcpy(for_test_arr, orig_arr, sizeof(int) * N[j]);

				double t = omp_get_wtime();
#pragma omp parallel num_threads(nthreads[i])
				{
#pragma omp single
					quicksort(for_test_arr, 0, N[j] - 1, Tr[m]);
				}
				t = omp_get_wtime() - t;
				printf("%d %.5lf\n", nthreads[i], t_ser / t);
			}

			printf("\n");
			free(orig_arr);
			free(for_test_arr);
		}
	}
	return 0;
}