#include <iostream>
#include <omp.h>

int main()
{
    int num_threads1 = 3;
    int num_threads2 = 2;

    // Первая параллельная область (выполняется, если num_threads1 > 2)
    #pragma omp parallel if(num_threads1 > 2)
    {
        int thread_num = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        #pragma omp critical
        {
            printf("Параллельная область 1 : \n");
            printf("Нить %i из %i\n", thread_num, num_threads);
        }
    }

    // Вторая параллельная область (выполняется, если num_threads2 > 2)
    #pragma omp parallel if(num_threads2 > 2)
    {
        int thread_num = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        #pragma omp critical
        {
            printf("Параллельная область 2 : \n");
            printf("Нить %i из %i\n", thread_num, num_threads);
        }
    }

    return 0;
}

