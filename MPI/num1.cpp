#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("Hello world rom process : %i, from : %i!\n", rank, size);
    MPI_Finalize();
}

// mpirun -n 8 ./num1

// Запускать программу с библиотекой MPI нужно с клучевым словом mpirun, -n 4 указывает сколько процессов мы запускаем 
// Не поняла, как нормально узнать количество процессов, но на практики мне не дали возможность > 8 процессов запустить
// Поэтому "запустить программу на всех процессах" = 8