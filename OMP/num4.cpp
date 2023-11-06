#include <iostream>
#include <omp.h>

int main() {
    const int size = 10;
    int a[size], b[size] = {0};

    for (int i = 0; i < size; i++) {
        a[i] = i;
        b[i] = i + 10;
    }

    int min_a = a[0], max_b = b[0];

    #pragma omp parallel num_threads(2)
    {
        int thread_num = omp_get_thread_num();

        if (thread_num == 0) {
            for (int i = 1; i < size; i++) {
                if (a[i] < min_a) min_a = a[i];
            }
        } else if (thread_num == 1) {
            for (int i = 1; i < size; i++) {
                if (b[i] > max_b) max_b = b[i];
            }
        }
    }

    printf("min a = %i\n", min_a);
    printf("max b = %i\n", max_b);

    return 0;
}


/*
    Тут распараллеливаем область, для того, чтобы в 1 потоке у нас искал min, а во 2 потоке max 
    Для чего? Чтобы сложность программы была не O(n^2), а O(n) по времени. 
*/