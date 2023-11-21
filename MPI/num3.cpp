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
    std::random_device rd; // std::random_device - доступ к устройству, которое генерит случайные числа, rd() - оператор для генерации случайного числа
    std::mt19937 gen(rd()); // std::mt19937 - это генератор случайных чисел Mersenne Twister, rd() - возвращает случаное начальное значение для генератора gen 
    std::uniform_real_distribution<> dis(-1.0, 1.0); // std::uniform_real_distribution - предоставляет распределение равномерно случайных вещественных чисел в заданном лиапозоне dist<> от -1 до 1 

    // Вычисление количества точек внутри круга
    for (long long i = rank; i < total_points; i += size) {
        double x = dis(gen), y = dis(gen);
        if (x * x + y * y <= 1.0)
            points_inside_circle++;
    }

    // Суммируем количество точек внутри круга со всех процессов
    long long total_inside_circle;
    MPI_Reduce(&points_inside_circle, &total_inside_circle, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Вычисляем число π
        double pi = (static_cast<double>(total_inside_circle) / static_cast<double>(total_points)) * 4.0;
        std::cout << "Вычисленное значение числа Пи : " << pi << std::endl;
    }

    MPI_Finalize();
}


// Если честно, даже задание не особо поняла, не то, что решение
// Разбираться жуть как не хочу, скип 