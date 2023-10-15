#include <iostream>
#include <omp.h>

const int x = 250;
void init(double m[x][x]);
void matrixVectorMultSequence(double m[x][x], double v[x], double res[x]);
void matrixVectorMultParallelism(double m[x][x], double v[x], double res[x]);
void print_matrix(double m[x][x]);

int main() {
    double m[x][x] = {0}, v[x] = {0}, res[x] = {0};
    // init(m);

    double stime = omp_get_wtime();
    matrixVectorMultSequence(m, v, res);
    double etime = omp_get_wtime();
    // print_matrix(m);
    double sequence_time  = etime - stime;

    stime = omp_get_wtime();
    matrixVectorMultParallelism(m, v, res);
    etime = omp_get_wtime();
    // print_matrix(m);
    double parallelism_time = etime - stime;

    printf("Время выполнения последовательной версии : %f секунд\n", sequence_time);
    printf("Время выполнения параллельной версии : %f секунд\n", parallelism_time);

    return 0;
}

void matrixVectorMultParallelism(double m[x][x], double v[x], double res[x]) {
    #pragma omp parallel for schedule(auto) num_threads(8)
    for (int i = 0; i < x; i++) {
        res[i] = 0.0; // Инициализируем результат
        for (int j = 0; j < x; j++) {
            res[i] += m[i][j] * v[j];
        }
    }
}

void matrixVectorMultSequence(double m[x][x], double v[x], double res[x]) {
    for (int i = 0; i < x; i++) {
        res[i] = 0.0;
        for (int j = 0; j < x; j++) {
            res[i] += m[i][j] * v[j];
        }
    }
}

void init(double m[x][x]) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < x; j++) {
            m[i][j] = rand() % 100;
        }
    }
}


void print_matrix(double m[x][x]) {
    printf("Матрица : \n");
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < x; j++) { 
            printf("%f ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/*
    По личным наблюдениям guided работает быстроее всего, массив нужно брать большой, 
    чтобы параллельное программирование имело смысл. 
*/