#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Получаем номер текущего процесса
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Получаем общее количество процессов

    // Вывод "Hello, world!" на каждом процессе
    std::cout << "Hello, world! from process " << rank << " of " << size << std::endl;

    MPI_Finalize();

    return 0;
}
