#include <iostream>
#include <omp.h>

int main() {
    int a = 10;
    int b = 20;

    printf("Значения переменных до входа в параллельную область :\n");
    printf("a = %i, b = %i\n", a, b);

    #pragma omp parallel num_threads(2) private(a) firstprivate(b)
    {
        int thread_num = omp_get_thread_num();
        a = 10;
        a += thread_num;
        b += thread_num;

        printf("Значения переменных внутри 1 параллельной области (нить %i) : \n", thread_num);
        printf("a = %i, b = %i\n", a, b);
    }

    #pragma omp parallel num_threads(4) shared(a) private(b)
    {
        int thread_num = omp_get_thread_num();
        b = 20;
        a -= thread_num;
        b -= thread_num;

        printf("Значения переменных внутри 2 параллельной области (нить %i) : \n", thread_num);
        printf("a = %i, b = %i\n", a, b);
    }

    printf("Значения переменных после выхода из параллельных областей :\n");
    printf("a = %i, b = %i\n", a, b);

    return 0;
}


/* 
Тут спрашивал про : 
    - private : каждый поток создаёт свою уникальную копию переменной, изменения в любом из потоков не влияет на другие потоки
    - firstprivate : этот атрибут похож на privatr, так как сохраняет создание уникальной копии переменной, 
        но при этому значение переменной инициализируется до входа в параллельную область
    - shared : эта переменная общая для каждого потока, изменения в одном потоке будет видны другим
*/