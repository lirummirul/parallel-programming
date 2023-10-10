#include <iostream>
#include <omp.h>

const int x = 12;

void printM(int m[]);
void parall1(int a[], int b[]);
void parall2(int a[], int b[], int c[]);

int main() {
    int a[x] = {0}, b[x] = {0}, c[x] = {0};
    parall1(a, b);
    printf("\n");
    parall2(a, b, c);

    printf("\nМатрица А : \n");
    printM(a);
    printf("\nМатрица B : \n");
    printM(b);
    printf("\nМатрица C : \n");
    printM(c);
}

void parall1(int a[], int b[]) {
    #pragma omp parallel num_threads(3)
    {
        int num_threads = omp_get_num_threads();
        int thread_num = omp_get_thread_num();

        // Вычисляем размер порции итераций для статического распределения
        int size = x / num_threads;
        
        // Вычисляем начальную и конечную итерацию для текущей нити
        // int start = thread_num * size;
        // int end = (thread_num == num_threads - 1) ? x : start + size;

        #pragma omp for schedule(static, size)
        for (int i = 0; i < x; i++) {
            a[i] = i + 1;
            b[i] = i + 2;
        }

        #pragma omp critical
        {
            // printf("Поток %i инициализировал элементы от %i до %i\n", thread_num, start, end - 1);
            printf("Поток %i инициализировал элементы статически\n", thread_num);

        }
    }
}

void parall2(int a[], int b[], int c[]) {
   #pragma omp parallel num_threads(4)
    {
        int num_threads = omp_get_num_threads();
        int thread_num = omp_get_thread_num();

        // Вычисляем размер порции итераций для динамического распределения
        int size = x / num_threads;

        #pragma omp for schedule(dynamic, size)
        for (int i = 0; i < x; i++) {
            c[i] = a[i] + b[i];
        }

        #pragma omp critical
        {
            printf("Поток %i вычислял элементы динамически\n", thread_num);
        }
    }
}

void printM(int m[]) {
    for (int i = 0; i < x; i++) 
        printf("%i ", m[i]);
    printf("\n");
}

