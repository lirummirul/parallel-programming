#include <iostream>
#include <random>
#include <mpi.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const long long total_points = 10000000; // Общее количество точек
    long long points_inside_circle = 0; // Количество точек внутри круга на каждом процессе

    // Инициализация генератора случайных чисел на каждом процессе
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    // Вычисление количества точек внутри круга
    for (long long i = rank; i < total_points; i += size) {
        double x = dis(gen);
        double y = dis(gen);
        if (x * x + y * y <= 1.0) {
            points_inside_circle++;
        }
    }

    // Суммируем количество точек внутри круга со всех процессов
    long long total_inside_circle;
    MPI_Reduce(&points_inside_circle, &total_inside_circle, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Вычисляем число π
        double pi = (static_cast<double>(total_inside_circle) / static_cast<double>(total_points)) * 4.0;
        std::cout << "Вычисленное значение числа Пи: " << pi << std::endl;
    }

    MPI_Finalize();
    return 0;
}
