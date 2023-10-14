#include <iostream>
#include <omp.h>

const int x = 6, y = 8;
void init(int d[x][y]);
void print_matrix(int d[x][y]);
void parall(int d[x][y]);

int main() {
    int d[x][y] = {0};
    init(d);
    print_matrix(d);
    parall(d);
    return 0;
}

void init(int d[x][y]) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            d[i][j] = rand() % 100;
        }
    }
}

void print_matrix(int d[x][y]) {
    printf("Матрица : \n");
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) { 
            printf("%i ", d[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void parall(int d[x][y]) {
    double avg = 0.0;
    int min, max = d[0][0], count = 0;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            double sum = 0.0;
            int thread_num = omp_get_thread_num();
            #pragma omp parallel for reduction(+:sum) // в этот момент мы создали параллельную область,
                                                      //  разделили через for все итерации на несколько потоков 
                                                      // и через дириктиву reduction(+:sum) результат всех потоков записали в эту переменную
            // в нашем случае каждый поток выполнит сумму и в переменную запишется сумма со всех потоков 
            for (int i = 0; i < x; i++) {
                for (int j = 0; j < y; j++) sum += d[i][j];
            }
            avg = sum / (x * x);
            printf("Нить : %i | Среднее арифметическое = %f\n", thread_num, avg);
        }

        #pragma omp section
        {
            int thread_num = omp_get_thread_num();
            #pragma omp parallel for reduction(min:min) reduction(max:max)
            for (int i = 0; i < x; i++) {
                for (int j = 0; j < y; j++) {
                    if (d[i][j] < min) min = d[i][j];
                    if (d[i][j] > max) max = d[i][j];
                }
            }
            printf("Нить : %i | Минимальное значение = %i\n", thread_num, min);
            printf("Нить : %i | Максимальное значение = %i\n", thread_num, max);
        }
        #pragma omp section
        {
            int thread_num = omp_get_thread_num();
            #pragma omp parallel for reduction(+:count)
            for (int i = 0; i < x; i++) {
                for (int j = 0; j < y; j++) {
                    if (d[i][j] % 5 == 0) count++;
                }
            }
            printf("Нить : %i | Количество чисел, кратных 5 = %i\n", thread_num, count);
        }
    }

}

/*
    Директива sections предоставляет возможность создания нескольких независимых секций кода,
    которые будут выполнены параллельно разными потоками.
    Это позволяет вам разделить ваш код на логически независимые части,
    которые могут выполняться одновременно, улучшая параллельную производительность.
    Внутри каждой секции может быть параллельная работа, как это определено с помощью других директив, таких как parallel или for.

    #pragma omp sections: Это директива начала секций. Она сообщает компилятору, что следующий блок кода будет разделен на секции.
    #pragma omp section: Эта директива используется внутри sections и помечает начало новой секции. 
    В пределах каждой секции может выполняться свой уникальный код.

*/