#include <iostream>
#include <omp.h>

int main() {
#pragma omp parallel num_threads(8)
	{
		int k = omp_get_thread_num();
		int size = omp_get_num_threads();
		printf("Hello World, thread %d out of %d\n", k, size);
	}
	return EXIT_SUCCESS;
}

