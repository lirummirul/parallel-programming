#include <iostream>
#include <omp.h>

int main() {
    int a = 10;
    int b = 20;

    printf("Значения переменных до входа в параллельную область :\n");
    printf("a = %i, b = %i\n", a, b);

    // Первая параллельная область (2 нити)
    #pragma omp parallel num_threads(2) private(a) firstprivate(b)
    {
        int thread_num = omp_get_thread_num();
        a = 10; // из-за того, что переменная a получена как приватная переменна, 
        // то инициализация до этой области не видна, чтобы это исправить, нужно инициализировать переменную внутри области
        a += thread_num;
        b += thread_num;

        printf("Значения переменных внутри 1 параллельной области (нить %i) : \n", thread_num);
        printf("a = %i, b = %i\n", a, b);
    }

    // Вторая параллельная область (4 нити)
    #pragma omp parallel num_threads(4) shared(a) private(b)
    {
        int thread_num = omp_get_thread_num();
        b = 20; // тут тоже самое, что и с переменной a в 1 области
        a -= thread_num;
        b -= thread_num;

        printf("Значения переменных внутри 2 параллельной области (нить %i) : \n", thread_num);
        printf("a = %i, b = %i\n", a, b);
    }

    printf("Значения переменных после выхода из параллельных областей :\n");
    printf("a = %i, b = %i\n", a, b);

    return 0;
}
