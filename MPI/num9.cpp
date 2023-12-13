#include<stdio.h> 
#include<mpi.h> 
#include<stdlib.h> 
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <math.h>
#include <ctime>

//9 задание (инвертирование массива)

int main(int argc, char* argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int arr_len = 10;

    int part_for_process = arr_len / size;

    if (arr_len % size != 0) {

        // тут делаем так, чтобы последнему процессу достались оставшиеся элементы массива
        if (rank == size - 1) part_for_process = arr_len - part_for_process * (size - 1);
    }

    int* arr = new int[arr_len];
    int* reversed_array = new int[arr_len];
    int* displs = new int[size];

    // сдвиг, когда принимаем на нулевом процессе
    int* recv_displs = new int[size];
    int* sendcounts = new int[size];

    int* local_arr = new int[part_for_process];

    if (rank == 0) {
        printf("Array: \n");
        for (int i = 0; i < arr_len; ++i) {
            arr[i] = i;
            printf("%d ", arr[i]);
        }
        printf("\n");

        for (int i = 0; i < size; ++i) {
            displs[i] = i * part_for_process;
            sendcounts[i] = part_for_process;
        }

        // отдельно обрабатываем случай для последнего процесса
        if (arr_len % size != 0) {
            sendcounts[size - 1] = arr_len - part_for_process * (size - 1);
        }

        // данные от последнего процесса будут размещены в буфере приема с начальным смещением 0
        recv_displs[size - 1] = 0;
        for (int i = size - 2; i >= 0; i--) {
            recv_displs[i] = recv_displs[i + 1] + sendcounts[i + 1];
        }
    }

    // Отправляем часть массива каждому процессу
    MPI_Scatterv(arr, sendcounts, displs, MPI_INT, local_arr, part_for_process, MPI_INT, 0, MPI_COMM_WORLD);

    // переворачиваем локальный массив
    for (int i = 0; i < part_for_process / 2; ++i) {
        int temp = local_arr[i];
        local_arr[i] = local_arr[part_for_process - i - 1];
        local_arr[part_for_process - i - 1] = temp;
    }

    // собираем всё: тут каждый процеес отправляет свою часть в перевернутом порядке
    MPI_Gatherv(local_arr, part_for_process, MPI_INT, reversed_array, sendcounts, recv_displs, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Reversed: \n");
        for (int i = 0; i < arr_len; ++i) {
            printf("%d ", reversed_array[i]);
        }
    }

    MPI_Finalize();
}
