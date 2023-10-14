#include <iostream>
#include <omp.h>

int main() {
#pragma omp parallel num_threads(8)
	{
		int k = omp_get_thread_num(); // номер того потока, который сейчас работает
		int size = omp_get_num_threads(); // количество всех потоков 
		printf("Hello World, thread %d out of %d\n", k, size);
	}
	return EXIT_SUCCESS;
}

/* 
Только просил показать, что программа работает 
*/