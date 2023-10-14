#include <iostream>
#include <omp.h>

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
    int count = 0;

    #pragma omp parallel for num_threads(4)
    for (int i = 0; i < x; i++) {
        if (a[i] % 9 == 0) {
            #pragma omp atomic
            count++;
        }
    }

    /*
    Опять же, что можно спросить препод : чем отличается atomic от critical
    Я это уже описывала в 6 задачке 
    */ 
    printf("Колличество элкментов, которые кратны 9 = %i\n", count);
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