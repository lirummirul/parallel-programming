#include <iostream>
#include <omp.h>
#include <cstdlib>

const int x = 30;
void init(int a[x]);
void print_matrix(int a[x]);
void parall(int a[x]);

int main() {
    int a[x] = {0};
    init(a);
    print_matrix(a);
    parall(a);
}

/*
Что такое замок? 
Это такое же средство синхронизации, как и директивы critical или atomic. 
В этой задаче замок ставиться на условие, если элемент > максимального значения
Только 1 поток может войти в это условие
Конкретно в этой задаче нет смысла использовать замок, критическую секцию или атомарную
Потому что очень навряд ли может произойти гонка данных (хотя я могу ошибаться)... 
В данном случае любое из ограничений создаёт излишнюю последовательность в параллельной области, хотя это не нужно
*/

void parall(int a[x]) {
    int max = 0;
    omp_lock_t lock;
    omp_init_lock(&lock); // инициализация замка. Создает и инициализирует замок.

    #pragma omp parallel for
    for (int i = 0; i < x; i++) {
        if (a[i] % 7 == 0) {
            omp_set_lock(&lock); // установка замка. Блокирует замок, пока он не станет доступным.
            if (a[i] > max)
                max = a[i];
            omp_unset_lock(&lock); // снятие замка. Разблокирует замок после его использования.
        }
    }

    omp_destroy_lock(&lock); // уничтожение замка. Освобождает ресурсы, связанные с замком.
    printf("Максимальный элемент, кратный 7 = %i\n", max);
}

void init(int a[x]) {
    #pragma omp parallel for num_threads(4)
    for (int i = 0; i < x; i++)
        a[i] = rand() % 100;
}

void print_matrix(int a[x]) {
    printf("Матрица : \n");
    for (int i = 0; i < x; i++) {
        printf("%i ", a[i]);
    }
    printf("\n\n");
}
