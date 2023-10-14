#include <iostream>
#include <omp.h>

const int x = 16000;
const int num_threads = 8;
const int size = 2000;

int parall1(int a[x], int b[x]);
void parall2(int a[x], int b[x]);
void parall3(int a[x], int b[x]);
void parall4(int a[x], int b[x]);
void printM(int m[]);

int main() {
    int a[x] = {0}, b[x] = {0};

    for (int i = 0; i < x; i++) a[i] = i;

    for (int type = 0; type < 4; type++) {
        double stime = omp_get_wtime();
        const char* name = nullptr;
        switch (type) {
            case 0 :
                stime = parall1(a, b);
                name = "static";
                break;
            case 1 :
                parall2(a, b);
                name = "dynamic";
                break;
            case 2 :
                parall3(a, b);
                name = "guided";
                break;
            case 3 :
                parall4(a, b);
                name = "auto";
                break;
        }
        double etime = omp_get_wtime();
        double diff = etime - stime;
        printf("Schedule type: %s, Elapsed time: %f sec\n", name, diff);
    }
}

int parall1(int a[x], int b[x]) {
    int ch = 0, stime = 0;
    printf("Введите размер порции : \n");
    std::cin >> ch;
    stime = omp_get_wtime();
    #pragma omp parallel for schedule(static, ch) num_threads(8)
    for (int i = 1; i < x - 1; i++) {
        int sum = a[i - 1] + a[i] + a[i + 1];
        b[i] = static_cast<double>(sum) / 3.0;
    }
    return stime;
}

void parall2(int a[x], int b[x]) {
    #pragma omp parallel for schedule(dynamic) num_threads(8)
    for (int i = 1; i < x - 1; i++) {
        int sum = a[i - 1] + a[i] + a[i + 1];
        b[i] = static_cast<double>(sum) / 3.0;
    }
}

void parall3(int a[x], int b[x]) {
    #pragma omp parallel for schedule(guided) num_threads(8)
    for (int i = 1; i < x - 1; i++) {
        int sum = a[i - 1] + a[i] + a[i + 1];
        b[i] = static_cast<double>(sum) / 3.0;
    }
}

void parall4(int a[x], int b[x]) {
    #pragma omp parallel for schedule(auto) num_threads(8)
    for (int i = 1; i < x - 1; i++) {
        int sum = a[i - 1] + a[i] + a[i + 1];
        b[i] = static_cast<double>(sum) / 3.0;
    }
}


void printM(int m[]) {
    for (int i = 0; i < x; i++) 
        printf("%i ", m[i]);
    printf("\n");
}


/*
Про static, про dynamic я уже расписывала

- guided : в этом режиме каждому потоку большая часть, но потом объём итераций с каждым разом уменьшается 
    Может оказаться так, что последнему потоку досталось меньше итераций, чем первому
    Это полезно, когда у нас есть много итерацией с одинаковой длительностью и немного итераций, требующих время. 
- auto или runtime : этот режим даёт возможность системе самостоятельно выбирать 

*/