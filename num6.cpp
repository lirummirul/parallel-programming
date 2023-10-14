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
    
    /*
    Этот способ подсчёта ср значения намного лучше, потому что каждый поток берёт на себя свою часть, а в конце соединяет свои результаты
    */

    #pragma omp parallel for
    for (int i = 0; i < x; i++) {
        avg_without_r += a[i];
    }
    
    /*
    Этот способ не безопасный, потому что мне самостоятельно по-хорошему нужно будет обеспечивать синхронизацию
    Тут суть, что несколько потоков могут обращаться к одной и той же переменной и может произойти гонка данных data race. 

    Может помочь создания критической области, то есть соединение всех потоков в 1 : 
    #pragma omp parallel for
    for (int i = 0; i < x; i++) {
        int local_sum = a[i];  // Каждый поток работает со своей локальной переменной

        #pragma omp critical
        {
            avg_without_r += local_sum;  // Обеспечиваем синхронизацию для обновления avg_without_r
        }
    }

    Но это не есть хорошо, вообще использовать директиву critical в распараллеливании не очень хорошо, ведь это создаёт последовательность
    Точнее, другие потоки ждут, пока критическая секция освободиться

    Можно использовать директиву atomic : 
    #pragma omp parallel for
    for (int i = 0; i < x; i++) {
        int local_sum = a[i];
        #pragma omp atomic
        avg_without_r += local_sum;
    }

    Эти 2 директивы похожи, но критическая секция может вмести в себя несколько строчек кода, а атомарна - нет

    Но обе эти директивы плохи в использовании, я объясняла причины чуть выше, в этой задаче куда лучше использовать reduction
    */

    avg_with_r /= x;
    avg_without_r /= x;

    printf("Среднее с reduction = %f\n", avg_with_r);
    printf("Среднее без reduction = %f\n", avg_with_r);

}

