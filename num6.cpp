#include <iostream>
#include <omp.h>

const int x = 100;
void init(int a[x]);
void print_matrix(int a[]);
void parall(int a[x]);

int main() {
    int a[x] = {0};
    init(a);
    print_matrix(a);
    parall(a);
    return 0;
}

void init(int a[x]) {
    for (int i = 0; i < x; i++) {
        a[i] = rand() % 100;
    }
}

void print_matrix(int a[x]) {
    printf("Матрица : \n");
    for (int i = 0; i < x; i++) {
        printf("%i ", a[i]);
    }
    printf("\n\n");
}

void parall(int a[x]) {
    double avg_with_r = 0.0, avg_without_r = 0.0;

    #pragma omp parallel for reduction(+:avg_with_r)
    for (int i = 0; i < x; i++) {
        avg_with_r += a[i];
    }

    #pragma omp parallel for
    for (int i = 0; i < x; i++) {
        avg_without_r += a[i];
    }

    avg_with_r /= x;
    avg_without_r /= x;

    printf("Среднее с reduction = %f\n", avg_with_r);
    printf("Среднее без reduction = %f\n", avg_with_r);

}