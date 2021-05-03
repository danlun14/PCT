#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>

// #define N 10000000
#define THRESHOLD 10000

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
	do {
		while (array[*i] < pivot) 
			(*i)++;
		while (array[*j] > pivot)
			(*j)--;
		if ((*i) <= (*j)) {
			swap(&array[*i], &array[*j]);
			(*i)++;
			(*j)--;
		}
	} while ((*i) <= (*j));
}

void quicksort(int *array, int low, int high)
{
	int i = 0;
	int j = 0;
	
	partition(array, &i, &j, low, high);

	if (high - low < THRESHOLD || j - low < THRESHOLD || high - i < THRESHOLD) {
		if (low < j) {
			quicksort(array, low, j);
		}
		if (i < high) {
			quicksort(array, i, high);
		}
	} else {
		#pragma omp task untied
		{
			quicksort(array, low, j);
		}
		quicksort(array, i, high);
	}

}

void init_array(int *array, int N)
{
	for (int i = 0; i < N; i++) {
		array[i] = rand() / (RAND_MAX + 1.0) * (100000 - 1) + 1;;
	}
}

int main()
{
	int N[5] = { 1000, 10000, 100000, 1000000, 10000000 };
	int nthreads[3] = { 1, 2, 4};
	double t_start = 0;
	FILE *f1 = fopen("th10000-N1000.txt","w");
	FILE *f2 = fopen("th10000-N10000.txt","w");
	FILE *f3 = fopen("th10000-N100000.txt","w");
	FILE *f4 = fopen("th10000-N1000000.txt","w");
	FILE *f5 = fopen("th10000-N10000000.txt","w");
	for (int j = 0; j < 5; j++) {
		printf("N = %d\n", N[j]);

		int *orig_arr = malloc(sizeof(int) * N[j]);
		int *for_test_arr = malloc(sizeof(int) * N[j]);

		init_array(orig_arr, N[j]);

		for (int i = 0; i < 3; i++) {
			memcpy(for_test_arr, orig_arr, sizeof(int) * N[j]);
			
			double t = omp_get_wtime();
			#pragma omp parallel num_threads(nthreads[i])
			{
				#pragma omp single
				quicksort(for_test_arr, 0, N[j] - 1);
			}
			t = omp_get_wtime() - t;
			if (nthreads[i] == 1){
				t_start = t;
			}
			
			printf("Time for %d threads = %.5lf, speedup = %lf\n", nthreads[i], t, t_start / t);
			if (N[j] == 1000){
				fprintf(f1,"%d %1.3lf\n", nthreads[i], t_start / t);
			}
			if (N[j] == 10000){
				fprintf(f2,"%d %1.3lf\n", nthreads[i], t_start / t);
			}
			if (N[j] == 100000){
				fprintf(f3,"%d %1.3lf\n", nthreads[i], t_start / t);
			}
			if (N[j] == 1000000){
				fprintf(f4,"%d %1.3lf\n", nthreads[i], t_start / t);
			}
			if (N[j] == 10000000){
				fprintf(f5,"%d %1.3lf\n", nthreads[i], t_start / t);
			}
		}

		printf("\n");
		free(orig_arr);
		free(for_test_arr);
	}

	return 0;
}