#include <iostream>
#include <omp.h>

int main() {
#pragma omp parallel num_threads(8) // создание 8 потоков 
	{
		int k = omp_get_thread_num(); // индификатор текущего потока
		int size = omp_get_num_threads(); // общее количество потоков
		printf("Hello World, thread %d out of %d\n", k, size);
	}
	return EXIT_SUCCESS;
}

/* Всегда ли вывод идентичен? Почему? 
	Вывод не всегда будет идентичен, так как это зависит от того, каким образом система управляет потоками и их планированием
*/

