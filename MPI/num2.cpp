#include <iostream>
#include <mpi.h>
#include <vector>
#include <algorithm>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
        const int x = 10;
    std::vector<int> data(x); // std::vector - это шаблонный класс c++, который создаёт динамический массив

    if (rank == 0) {
        // Инициализация массива данными в корневом процессе
        for (int i = 0; i < x; ++i) {
            data[i] = rand() % 100; 
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

   // Находим максимальный элемент в локальном массиве
    int localMax = 0;
    // *std::max_element(data.begin(), data.end());
    int globalMax = 0; // Глобальный максимум
    
    int localCount = x / size;
    std::vector<int> localData(localCount);

    MPI_Scatter(data.data(), localCount, MPI_INT, localData.data(), localCount, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < localCount; i++) {
        if (localData[i] > localMax) { 
            localMax = localData[i];
        }
    }
    // Выполняем редукцию для нахождения максимального значения
    MPI_Reduce(&localMax, &globalMax, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    /*
    1 - максимум от каждого процесса 
    2 - куда записывать 
    3 - количестово элментов, переданные от каждого процесса (у нас 1 макс от каждого)
    4 - тип данных 
    5 - что найти нужно (можно указать сумму, разницу, мин/ макс и т.п)
    6 - ранг процесса получаетеля, на мастер потоке считаем reduce 
    7 - аргумент, который говорит, что операция выполныется между всеми процессами 
    */

    if (rank == 0)
        printf("Максимальное число в массиве : %i\n", globalMax);

    MPI_Finalize();
}


// /*
// mpirun -n 4 ./num2

// send, recv, bcast и reduce - это основные функции библиотеки MPI для 
// обмена данными между процессами в параллельных вычислениях.

// MPI_Send и MPI_Recv:
//     MPI_Send и MPI_Recv используются для явной отправки и получения 
// сообщений между процессами. Они позволяют передавать данные от одного процесса к другому. 
// MPI_Send используется для отправки данных, а MPI_Recv для их приема.



// MPI_Bcast:
//     MPI_Bcast используется для широковещательной передачи сообщения от 
// одного процесса ко всем остальным. Один процесс отправляет данные, 
// а все остальные их получают. Данная операция предназначена для передачи 
// одного и того же сообщения всем процессам.


// MPI_Reduce:
//     MPI_Reduce выполняет операцию редукции (например, суммирование, 
// поиск максимума и т.д.) над данными, полученными от всех процессов, и 
// возвращает результат на одном из процессов. Эта операция позволяет выполнить 
// глобальное сокращение результатов, полученных от каждого процесса.
// */

// // TODO:  Вот тут нужно изменить заполнение массивом, снести барьеры и изменить дублирование reduce