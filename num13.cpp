#include <iostream>
#include <omp.h>
#include <semaphore.h>

void parall1();
void parall2();
void parall3();
void parall4();
void parall5();

int main() {
    char str[256], *num=str;
    int digit = 0;
    printf("Введите число от 1 до 5 : \n");
    std::cin >> str;
    while (str[0] != '-' && str[1] != '1') {
        if (!isdigit(*num)) parall1();
        else {
            digit=atoi(str);
            switch (digit) {
                case 1 :
                    parall1();
                    break;
                case 2 :
                    parall2();
                    break;
                case 3 :
                    parall3();
                    break;
                case 4 :
                    parall4();
                    break;
                case 5 :
                    parall5();
                    break;
                default :
                    parall1();
                    break;
            }
        }
        std::cin >> str;
    }
}

void parall1() {
    printf("Способ № 1 : \n");

    int thread_ids[8]; // Массив для хранения идентификаторов потоков

    #pragma omp parallel num_threads(8)
    {
        int k = omp_get_thread_num();
        thread_ids[k] = k; // Сохраняем идентификатор потока
    }

    // Выводим идентификаторы в обратном порядке
    for (int i = 7; i >= 0; i--) {
        int k = thread_ids[i];
        int size = 8;
        printf("Hello World, thread %d out of %d\n", k, size);
    }
}

void parall2() {
    printf("Способ № 2 : \n");
    #pragma omp parallel num_threads(8)
    {
        int size = omp_get_num_threads();

    #pragma omp single
        {
            for (int i = size - 1; i >= 0; i--)
                printf("Hello World, thread %d out of %d\n", i, size);
        }
    }
}

void parall3() {
    printf("Способ № 3 : \n");
    int size = 8;
    int thread_ids[8];

    #pragma omp parallel num_threads(8)
    {
        int k = omp_get_thread_num();
        thread_ids[k] = k;
    }

    #pragma omp parallel for ordered
    for (int i = size - 1; i >= 0; i--) {
        int k = thread_ids[i];
    #pragma omp ordered
        {
            printf("Hello World, thread %d out of %d\n", k, size);
        }
    }
}

void parall4() {
    printf("Способ № 4 : \n");
    #pragma omp parallel num_threads(8)
    {
        int size = omp_get_num_threads();
    #pragma omp master
        {
            for (int i = size - 1; i >= 0; i--)
                printf("Hello World, thread %d out of %d\n", i, size);
        }
    }
}

void parall5() {
    printf("Способ № 5 : \n");
    #pragma omp parallel num_threads(8)
    {
        int size = omp_get_num_threads();

        int k = omp_get_thread_num();
        for (int i = size - 1; i >= 0; i--) {
        #pragma omp barrier
            {
                if (i == omp_get_thread_num()) {
                #pragma omp critical
                    printf("Hello World, thread %d out of %d\n", k , size);
                }
            }
        }
    }
}

