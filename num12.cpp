#include <iostream>
#include <omp.h>
#include <cstdlib>

const int x = 30;
void init(int a[x]);
void print_matrix(int a[x]);
void parall(int a[x]);

int main() {
    int a[x] = {0};
    init(a);
    print_matrix(a);
    parall(a);
}

void parall(int a[x]) {
    int max = 0;
    omp_lock_t lock;
    omp_init_lock(&lock);

    #pragma omp parallel for
    for (int i = 0; i < x; i++) {
        if (a[i] % 7 == 0) {
            omp_set_lock(&lock);
            if (a[i] > max)
                max = a[i];
            omp_unset_lock(&lock);
        }
    }

    omp_destroy_lock(&lock);
    printf("Максимальный элкмент, кратный 7 = %i\n", max);
}

void init(int a[x]) {
    #pragma omp parallel for num_threads(4)
    for (int i = 0; i < x; i++)
        a[i] = rand() % 100;
}

void print_matrix(int a[x]) {
    printf("Матрица : \n");
    for (int i = 0; i < x; i++) {
        printf("%i ", a[i]);
    }
    printf("\n\n");
}
