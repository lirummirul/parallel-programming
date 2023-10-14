#include <iostream>
#include <omp.h>

int main() {
    int num_threads1 = 3;
    int num_threads2 = 2;

    #pragma omp parallel if(num_threads1 > 2) num_threads(num_threads1)
    {
        int thread_num = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        #pragma omp critical
        {
            printf("Параллельная область 1 : \n");
            printf("Нить %i из %i\n", thread_num, num_threads);
        }
    }

    #pragma omp parallel if(num_threads2 > 2) num_threads(num_threads2)
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

/*
Смысл задачи в том, что мы пишем условие для параллельной области 
Мы изначально прописываем для 1 и 2 области количество нитий 
И смысл в том, чтобы посмотреть, что будет, если условие выполняется, и что будет, если нет 

В 1 области условие выполниться, потому что количество нитий > 3, мы зашли в условие, показали потоки 
Во 2 области условие не выполняется, но код всё равно заходит в критическую область. 
В задание было указано : "если заданное значение числа нитей больше 2, область выполняется параллельно, иначе не параллельно"
То есть тут мы зашли в параллельную область, но выполнили код последовательно
*/