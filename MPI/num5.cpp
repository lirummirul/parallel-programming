#include <iostream>
#include <vector>
#include <mpi.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int vectorSize = 8; // Размер векторов
    std::vector<int> vectorA(vectorSize);
    std::vector<int> vectorB(vectorSize);

    for (int i = 0; i < vectorSize; ++i) {
        vectorA[i] = i + 1;
        vectorB[i] = vectorSize - i;
    }

    MPI_Barrier(MPI_COMM_WORLD);

    std::cout << "VectorA процесс : " << rank << ": содержимое массива data: ";
    for (int i = 0; i < vectorSize; ++i)
        std::cout << vectorA[i] << " ";
    std::cout << std::endl;

    std::cout << "VectorB процесс : " << rank << ": содержимое массива data: ";
    for (int i = 0; i < vectorSize; ++i)
        std::cout << vectorB[i] << " ";
    std::cout << std::endl;

    std::vector<int> localVectorA(vectorSize / size);
    std::vector<int> localVectorB(vectorSize / size);

    // Распределение данных через Scatterv
    std::vector<int> sendCounts(size, vectorSize / size);
    std::vector<int> displacements(size, 0);
    for (int i = 1; i < size; ++i)
        displacements[i] = displacements[i - 1] + vectorSize / size;

    MPI_Scatterv(vectorA.data(), sendCounts.data(), displacements.data(), MPI_INT, localVectorA.data(), vectorSize / size, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatterv(vectorB.data(), sendCounts.data(), displacements.data(), MPI_INT, localVectorB.data(), vectorSize / size, MPI_INT, 0, MPI_COMM_WORLD);

    int localDotProduct = 0;

    // Вычисление локальной суммы произведений соответствующих координат
    for (int i = 0; i < vectorSize / size; ++i)
        localDotProduct += localVectorA[i] * localVectorB[i];

    int globalDotProduct;

    // Сбор результатов операцией Reduce
    MPI_Reduce(&localDotProduct, &globalDotProduct, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
        std::cout << "Скалярное произведение векторов: " << globalDotProduct << std::endl;

    MPI_Finalize();
}
