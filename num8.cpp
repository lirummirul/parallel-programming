#include <iostream>
#include <omp.h>

const int x = 16000;
const int num_threads = 8;
const int size = 2000;

void printM(int m[]);

int main() {
    int a[x] = {0}, b[x] = {0};

    for (int i = 0; i < x; i++)
        a[i] = i;

    for (int type = 0; type < 4; type++) {
        double stime = omp_get_wtime();

        if (type = 0)
        #pragma omp parallel for schedule(runtime) num_threads(8)
        for (int i = 1; i < x - 1; i++) {
            int sum = a[i - 1] + a[i] + a[i + 1];
            b[i] = static_cast<double>(sum) / 3.0;
        }

        double etime = omp_get_wtime();
        double diff = etime - stime;

        const char* name = nullptr;
        switch (type) {
            case 0:
                name = "static";
                break;
            case 1:
                name = "dynamic";
                break;
            case 2:
                name = "guided";
                break;
            case 3:
                name = "auto";
                break;
            default:
                name = "unknown";
                break;
        }

        printf("Schedule type: %s, Elapsed time: %f sec\n", name, diff);
    }

}

void printM(int m[]) {
    for (int i = 0; i < x; i++) 
        printf("%i ", m[i]);
    printf("\n");
}
