#include <iostream>
#include <mpi.h>
#include <vector>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int arraySize = 16; // Размер исходного массива
    std::vector<int> data(arraySize);
    int localCount = arraySize / size;

    // Заполнение массива случайными числами (на каждом процессе)
    for (int i = 0; i < arraySize; ++i)
        data[i] = (i - arraySize / 2); // Пример заполнения массива значениями

    MPI_Barrier(MPI_COMM_WORLD); // Синхронизация всех процессов

    std::cout << "Процесс " << rank << ": содержимое массива data: ";
    for (int i = 0; i < arraySize; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;

    std::vector<int> localData(localCount);

    // Распределение данных через Scatterv
    std::vector<int> sendCounts(size, localCount);
    std::vector<int> displacements(size, 0);
    for (int i = 1; i < size; ++i) {
        displacements[i] = displacements[i - 1] + localCount;
    }

    MPI_Scatterv(data.data(), sendCounts.data(), displacements.data(), MPI_INT,
                 localData.data(), localCount, MPI_INT, 0, MPI_COMM_WORLD);

    int localSum = 0;
    int localPositiveCount = 0;

    // Вычисление локальной суммы и количества положительных чисел
    for (int i = 0; i < localCount; ++i) {
        if (localData[i] > 0) {
            localSum += localData[i];
            localPositiveCount++;
        }
    }

    int globalSum;
    int globalPositiveCount;

    // Сбор результатов операцией Reduce с двумя числами
    MPI_Reduce(&localSum, &globalSum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&localPositiveCount, &globalPositiveCount, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double average = static_cast<double>(globalSum) / static_cast<double>(globalPositiveCount);
        std::cout << "Среднее арифметическое среди положительных чисел: " << average << std::endl;
    }

    MPI_Finalize();
    return 0;
}
