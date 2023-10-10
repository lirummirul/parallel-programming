#include <iostream>
#include <omp.h>

void parall1();
void parall2();
void parall3();
void parall4();
void parall5();

int main() {
    int num = 0;
    printf("Введите число от 1 до 5 : \n");
    scanf("%i", &num);
    switch (num) {
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

void parall1() {
    printf("Способ № 1 : \n");
    omp_lock_t lock;
    omp_init_lock(&lock);

    #pragma omp parallel num_threads(8)
    {
        int k = omp_get_thread_num();
        int size = omp_get_num_threads();
        omp_set_lock(&lock);
        printf("Hello World, thread %d out of %d\n", size - k - 1, size);
        omp_unset_lock(&lock);
    }
    omp_destroy_lock(&lock);
}

void parall2() {
    printf("Способ № 2 : \n");
    #pragma omp parallel num_threads(8)
    {
        // int k = omp_get_thread_num();
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
        // int k = omp_get_thread_num();
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
    int thread_ids[8] = {0};
    #pragma omp parallel num_threads(8)
    {
        int k = omp_get_thread_num();
        thread_ids[k] = k;
    }

    int size = omp_get_num_threads();
    for (int i = size - 1; i >= 0; i--)
        printf("Hello World, thread %d out of %d\n", thread_ids[i], size);
}