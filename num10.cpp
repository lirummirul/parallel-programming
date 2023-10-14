#include <iostream>
#include <omp.h>
#include <climits>

const int x = 6, y = 8;
void init(int d[x][y]);
void print_matrix(int d[x][y]);
void parall(int d[x][y]);

int main() {
    int d[x][y] = {0};
    init(d);
    print_matrix(d);
    parall(d);
}

void parall(int d[x][y]) {
    int min = INT_MAX;
    int max = INT_MIN;

    #pragma omp parallel for num_threads(4)
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            #pragma omp critical
            {
                if (d[i][j] < min)
                    min = d[i][j];
                if (d[i][j] > max)
                    max = d[i][j];
            }
        }
    }

    /*
    Тут фактически и просят сделать то, о чём я писала в 6 номере, нужно написать аналог reduction
    Это аналог, но он очень плох, мы фактически создаём последовательность в параллельной области
    */

    printf("Max = %i\n", max);
    printf("Min = %i\n", min);

}

void init(int d[x][y]) {
    #pragma omp parallel for num_threads(4)
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++)
            d[i][j] = rand() % 100;
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
