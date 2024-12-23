# Отчет по лабораторной работе №1 по курсу "Объектно-ориентированное программирование"

Студент: Моисеев Кирилл Всеволодович \
Учебная группа: M8О-215Б-23 \
Контакты: kloshka05@mail.ru \
Работа выполнена: 09.09.2024\
Преподаватель: Зайцев Данила Евгеньевич

## 1. Тема

Первая программа на C++

## 2. Цель работы

1) Научится писать простые программы, использующие ввод/вывод через потоки std::cin, std::cout
2) Изучить базовые операторы и конструкции C++
3) Изучить систему сборки CMake
4) Изучить библиотеку для написания unit-тестов Google Test

## 3. Задание

16 Напишите программу, которая вычисляет наибольший общий делитель двух чисел

## 4. Оборудование

Процессор: i7 1165g7 \
ОП: 16 Гб \
НМД: 512 Гб \
Монитор: 1920x1080

## 5. Программное обеспечение

Операционная система семейства: **linux mint (ubuntu)**, версия **21.2** \
Интерпретатор команд: **bash**, версия **5.1.16** \
Среда разработки: **Visual Studio Code**, версия **1.93.0** \
Редактор текстов: **vim**, версия **8.2.2121** \
Утилиты операционной системы: **make, cmake** \
Прикладные системы и программы: **--** \
Местонахождение и имена файлов программ и данных на домашнем компьютере: **C:\Users\klosh\Desktop\test\MyCppProject**

## 6. Идея, метод, алгоритм решения задачи

Алгоритм Евклида для нахождения НОД:
Пока второе число не равно нулю:
    Заменить первое число на второе.
    Заменить второе число на остаток от деления первого на второе.
Когда второе число станет нулём, первое число — это НОД.
## 7. Сценарий выполнения работы

План:

1. Считать через поток std::cin числа.
2. Вычисить ответ, используя программную реализацию описанного выше алгоритма.

## 8. Распечатка протокола

```
enter left value:9
enter right value:21
result: 3

enter left value:19 
enter right value:17
result: 1

enter left value:-10
enter right value:20
result: 10
```

## 9. Дневник отладки

| №   | Лаб. или дом. | Дата       | Время | Событие                                                                                                        | Действие по исправлению | Примечание |
|:---:|:-------------:|:----------:|:-----:|:--------------------------------------------------------------------------------------------------------------:|:-----------------------:|:----------:|
| 1 | Дом | 08.09.2024 | 23:20 | Невозможность сборки проекта с помощью инструкции к первой лабораторной работе (возможно они только для unix систем) | Заменил последовательность команд в инструкции на заменил ее на cmake -G "MinGW Makefiles" .. ; mingw32-make ; mingw32-make install | спасибо GPT |
| 2 | Дом | 09.09.2024 | 04:20 | Не учел случай, когда числа отрицательные| изменил функцию поиска НОД: стал заменять числа на их модуль|   |
| 3 | Дом | 09.09.2024 | 05:00 | Отсутствие unit-тестов | Добавил unit-тесты с помощью фреймворка Google Test |   |


## 10. Замечания автора по существу работы

Решение своего варианта лабораторной работы заняло у меня не более 2 часов со всеми правками, но из-за необходимости интеграции CMake и Google Test, на данную лабораторную работу были потрачены примерно одни сутки. Было приятно вспомнить базовые конструкции, вновь программируя на C++

## 11. Выводы

Я вспомнил, как надо работать с потоками std::cin, std::cout, с базовыми операторами и конструкциями C++. Я научился использовать CMake для сборки проекта и Google Test для unit-тестирования проекта