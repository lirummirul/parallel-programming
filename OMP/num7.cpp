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
        printf("%i\n", num_threads);

        #pragma omp for schedule(static, size)
        for (int i = 0; i < x; i++) {
            a[i] = i + 1;
            b[i] = i + 2;
        }

        /*
        Разделение итераций в статическом режиме происходит заранее, мы уже указываем размер порции, 
        то есть сейчас мы делим 12 на 3 на 4 части мы разделим цикл for
        */

        #pragma omp critical
        {
            printf("Поток %i инициализировал элементы статически\n", thread_num);

        }
    }
}

void parall2(int a[], int b[], int c[]) {
   #pragma omp parallel num_threads(4)
    {
        int thread_num = omp_get_thread_num();

        #pragma omp for schedule(dynamic)
        for (int i = 0; i < x; i++)
            c[i] = a[i] + b[i];

        /*
        Тут цикл мы разделили динамически, это было бы полезно, если бы в цикле не все операции имели бы одинаковый вес 
        То есть каждый поток наберает себе итерацию, как только он заканчивает, берёт себе новую
        Возмонжо это может тут пригодиться, если бы внутри фора были бы ещё какие-нибудь условия и функции, 
        но сейчас не вижу явной разницы между статиком
        */

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

