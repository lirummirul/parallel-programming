# Parallel Programming

## Задачи : 
1. Написать программу где каждый поток печатает свой идентификатор, количество потоков всего и строчку «Hello World». Запустить программу с 8 потоками. Всегда ли вывод идентичен? Почему?
2. Написать программу, в которой определить две параллельные области, выполнение которых зависит от условного оператора #pragma omp parallel if(…), если заданное значение числа нитей больше 2, область выполняется параллельно, иначе не параллельно. Число нитей перед первой областью задать равным 3, перед второй – равным 2. Внутри параллельных областей определить количество нитей и номер каждой нити, результат выдать на экран. Убедиться в правильности работы программы.
3. Написать программу, в которой объявить и присвоить начальные значения целочисленным переменным: a и b, определить две параллельные области, первая – с числом нитей 2, вторая – с числом нитей 4. Для первой области переменные a и b объявить защищенными, с режимом доступа private и firstprivate соответственно, внутри области определить номер нити и выполнить увеличение значения переменных на эту величину. Выдать на экран значения переменных до входа в параллельную область, внутри параллельной области и после выхода из параллельной области. Для второй области переменную a объявить общей, переменную b объявить защищенной, с режимом доступа private, определить номер нити и выполнить уменьшение значения переменных на эту величину. Выдать на экран значения переменных до входа в параллельную область, внутри параллельной области и после выхода из параллельной области. Неинициализированные переменные инициализировать.
