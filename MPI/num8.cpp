#include<stdio.h> 
#include<mpi.h> 
#include<stdlib.h> 
#include <vector>
#include <algorithm>

//8 задание (Scatter и Gather через Send и Recv)

int main(int argc, char* argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int arr_len = 20;

    int part_for_process = arr_len / size;


    int* arr = new int[arr_len];
    int* local_arr = new int[part_for_process];
    int* result_arr = new int[arr_len];

    if (rank == 0) {

        printf("Array: ");
        for (int i = 0; i < arr_len; ++i) {
            arr[i] = i;
            printf("%d ", arr[i]);
        }
        printf("\n\n");

        // с 0 процесса отправляем всем остальным
        for (int i = 0; i < size; ++i) {
            int* send_buf = new int[part_for_process];
            for (int j = 0; j < part_for_process; ++j) {
                send_buf[j] = arr[i * part_for_process + j];
            }

            if (i == 0) local_arr = send_buf;
            else MPI_Send(send_buf, part_for_process, MPI_INT, i, i + 10, MPI_COMM_WORLD);
        }
    }

    // на всех остальных процессаах получаем
    if (rank != 0) {
        MPI_Recv(local_arr, part_for_process, MPI_INT, 0, rank + 10, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
    }

    printf("rank = %d\n", rank);
    for (int i = 0; i < part_for_process; ++i) {
        printf("%d ", local_arr[i]);
    }
    printf("\n\n");

    if (rank != 0) {
        // со всех процессов отправляем 0 свою часть
        MPI_Send(local_arr, part_for_process, MPI_INT, 0, rank + 100, MPI_COMM_WORLD);
    }
    else {
        // заполняем на 0 процессе результирующий массив из буфера 0 процесса
        for (int i = 0; i < part_for_process; ++i) {
            result_arr[i] = local_arr[i];
        }
    }

    if (rank == 0) {
        // получаем данные и заполняем ими массив
        for (int i = 1; i < size; ++i) {
            MPI_Recv(local_arr, part_for_process, MPI_INT, i, i + 100, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
            for (int j = 0; j < part_for_process; ++j) {
                result_arr[i * part_for_process + j] = local_arr[j];
            }
        }

        printf("Result array: ");
        for (int i = 0; i < arr_len; ++i) {
            printf("%d ", result_arr[i]);
        }
    }

    MPI_Finalize();
}
