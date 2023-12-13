#include <iostream>
#include <vector>
#include <mpi.h>

// ТАК ! На процессах > 2 у меня аборт, исправлять и вникать не хочу, но надо не забыть об этом(!)

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int rowCount = 8, columnCount = 8;
    const int localRowCount = rowCount / size; // Количество строк для каждого процесса = 2 

    std::vector<std::vector<int>> matrix(rowCount, std::vector<int>(columnCount)); 
    // так происходит создание динамического двумерного массива, выделяем память под строки и столбцы отдельно

    // for (int i = 0; i < rowCount; ++i) {
    //     for (int j = 0; j < columnCount; ++j)
    //         matrix[i][j] = (i * columnCount) + j + 1;
    // }

    // ТаК, прикол не понят... Одинаковые массивы, но в 1 случае говорит : седловой точки нет, во 2 - есть 57... НЮАНС 
    matrix = {
        { 1, 2, 3, 4, 5, 6, 7, 8 },
        { 9, 10, 11, 12, 13, 14, 15, 16 },
        { 17, 18, 19, 20, 21, 22, 23, 24 },
        { 25, 26, 27, 28, 29, 30, 31, 32 },
        { 33, 34, 35, 36, 37, 38, 39, 40 },
        { 41, 42, 43, 44, 45, 46, 47, 48 },
        { 49, 50, 51, 52, 53, 54, 55, 56 },
        { 57, 58, 59, 60, 61, 62, 63, 64 }
    };

    std::cout << "Процесс : " << rank << ": содержимое массива matrix : \n";
    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < columnCount; ++j)
            std::cout << matrix[i][j] << " ";
        std::cout << std::endl;
    }

    std::vector<int> sendCounts(size, localRowCount * columnCount);
    std::vector<int> displacements(size, 0);
    for (int i = 1; i < size; ++i)
        displacements[i] = displacements[i - 1] + localRowCount * columnCount;

    std::vector<int> localMatrix(localRowCount * columnCount);
    
    MPI_Scatterv(matrix.data(), sendCounts.data(), displacements.data(), MPI_INT, localMatrix.data(), localRowCount * columnCount, MPI_INT, 0, MPI_COMM_WORLD);


    // ------------------------------------------
    // Локальные вычисления
    std::vector<int> localMinima(localRowCount);

    // Проходимся по строкам процесса 
    for (int i = 0; i < localRowCount; ++i) {
        int min = localMatrix[i * columnCount];
        for (int j = 1; j < columnCount; ++j) {
            if (localMatrix[i * columnCount + j] < min)
                min = localMatrix[i * columnCount + j];
        }
        localMinima[i] = min;
    }

    int localMaxMin = *std::max_element(localMinima.begin(), localMinima.end());

    // Сбор результатов операцией Reduce
    int globalMaxMin;
    MPI_Reduce(&localMaxMin, &globalMaxMin, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        std::vector<int> minMax(columnCount);
        for (int j = 0; j < columnCount; ++j) {
            int max = matrix[0][j];
            for (int i = 1; i < rowCount; ++i) {
                if (matrix[i][j] > max)
                    max = matrix[i][j];
            }
            minMax[j] = max;
        }

        int globalMinMax = *std::min_element(minMax.begin(), minMax.end());

        if (globalMaxMin == globalMinMax)
            std::cout << "Седловая точка найдена: " << globalMaxMin << std::endl;
        else
            std::cout << "Седловая точка не найдена. MaxMin : " << globalMaxMin << " и MinMax : " << globalMinMax << std::endl;
    }

    MPI_Finalize();
}


/*
Седловая точка в матрице - это такой элемент, 
который является минимумом в своей строке и максимумом в своем столбце. 
*/ 