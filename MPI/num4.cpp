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
    int localCount = 0;
    //  = arraySize / size;;
    if (arraySize % size != 0) localCount = arraySize / size + 1;
    else localCount = arraySize / size;
    //  = arraySize / size; // я запускаю на 4 процесса => 16 / 4 = 4
    // это количество элементов, которые каждый процесс ожидает получить в результате операции MPI_Scatterv

    if (rank == 0) {
        for (int i = 0; i < arraySize; ++i) {
            if (i % 2 == 0) data[i] = (i - arraySize * rank / 2);
            else data[i] = (i - arraySize / 2);
             std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    std::vector<int> localData(localCount); // массив с локальными данными (для каждого процесса, как я поняла) размером = 4 

    // Распределение данных через Scatterv
    std::vector<int> sendCounts(size, localCount); // Значения в этом векторе указывают, 
    // сколько элементов отправляется каждому процессу в результате операции MPI_Scatterv. 
    // Здесь size - это общее количество процессов в коммуникаторе, а localCount - количество 
    // элементов данных, которые каждый процесс отправит. В итоге вектор sendCounts будет 
    // содержать size элементов, все равные localCount.

    std::vector<int> displacements(size, 0); // смещение для каждого процесса в буфере data
    // Начальное смещение для каждого процесса устанавливается в ноль, а затем через цикл вычисляются остальные смещения
    for (int i = 1; i < size; ++i)
        displacements[i] = displacements[i - 1] + localCount;

    MPI_Scatterv(data.data(), sendCounts.data(), displacements.data(), MPI_INT, localData.data(), localCount, MPI_INT, 0, MPI_COMM_WORLD);
    /*
    функция для распределения блоков данных между процессами
    1 - указатель на начало буффера
    2 - массив, указывающий количество элементов данных, которые будут отправлены каждому процессу
    3 - displacements
    4 - тип данных 
    5 - указатель на буфер, в который будут получены данные. Этот буфер должен быть доступен на каждом процессе, включая корневой процесс
    6 - количество элементов данных, которые каждый процесс ожидает получить.
    7 - корневой процесс 
    8 - аргумент, который говорит, что операция выполныется между всеми процессами
    */
    
    int localSum = 0; 
    int localPositiveCount = 0;

    // Вычисление локальной суммы и количества положительных чисел
    for (int i = 0; i < localCount; ++i) {
        if (localData[i] > 0) {
            localSum += localData[i];
            localPositiveCount++;
        }
    }
    // Что происходит выше, кажется мне понятным без коментариев 

    int globalResults[2];

    int localResults[2];
    localResults[0] = localSum;
    localResults[1] = localPositiveCount;

    MPI_Reduce(localResults, globalResults, 2, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);


    // // Сбор результатов операцией Reduce с двумя числами
    // MPI_Reduce(&localSum, &globalSum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); // на каждом процессе вычисляем локальную сумму, потом находим сумму со всех процессов
    // MPI_Reduce(&localPositiveCount, &globalPositiveCount, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); // на каждом процесе 

    if (rank == 0) {
        double average = static_cast<double>(globalResults[0]) / static_cast<double>(globalResults[1]);
        std::cout << "Среднее арифметическое среди положительных чисел: " << average << std::endl;
    }

    MPI_Finalize();
}
