#include <iostream>
#include <mpi.h>
#include <vector>
#include <algorithm>

const int x = 10; // Размер массива

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::vector<int> data(x);

    // Инициализация массива случайными числами (на каждом процессе)
    for (int i = 0; i < x; ++i)
        data[i] = (rank * x) + i; // Пример заполнения массива значениями

    MPI_Barrier(MPI_COMM_WORLD); // Синхронизация всех процессов

    std::cout << "Процесс " << rank << ": содержимое массива data: ";
    for (int i = 0; i < x; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;

   // Находим максимальный элемент в локальном массиве
    int localMax = *std::max_element(data.begin(), data.end());
    int globalMax; // Глобальный максимум

    // Выполняем редукцию для нахождения максимального значения
    MPI_Reduce(&localMax, &globalMax, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0)
        printf("Максимальное число в массиве : %i\n", globalMax);

    MPI_Finalize();
}


/*
mpirun -n 4 ./num2


send, recv, bcast и reduce - это основные функции библиотеки MPI для 
обмена данными между процессами в параллельных вычислениях.

MPI_Send и MPI_Recv:
MPI_Send и MPI_Recv используются для явной отправки и получения 
сообщений между процессами. Они позволяют передавать данные от одного процесса к другому. 
MPI_Send используется для отправки данных, а MPI_Recv для их приема.



MPI_Bcast:
MPI_Bcast используется для широковещательной передачи сообщения от 
одного процесса ко всем остальным. Один процесс отправляет данные, 
а все остальные их получают. Данная операция предназначена для передачи 
одного и того же сообщения всем процессам.


MPI_Reduce:
MPI_Reduce выполняет операцию редукции (например, суммирование, 
поиск максимума и т.д.) над данными, полученными от всех процессов, и 
возвращает результат на одном из процессов. Эта операция позволяет выполнить 
глобальное сокращение результатов, полученных от каждого процесса.
*/