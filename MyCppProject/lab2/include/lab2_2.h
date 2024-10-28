#ifndef HEX_H
#define HEX_H

#include <string>
#include <stdexcept>
using namespace std;
class Hex {
public:
    // Конструкторы
    Hex();
    Hex(const string &hexStr); // Инициализация строкой
    Hex(const Hex& other);          // Конструктор копирования
    Hex(Hex&& other) noexcept;      // Конструктор перемещения
    ~Hex();                         // Деструктор

    // Методы присваивания
    void assign(const Hex &other);
    void assignMove(Hex &&other) noexcept;

    // Арифметические операции
    void add(const Hex &other);     // Сложение
    void subtract(const Hex &other);// Вычитание

    // Операции сравнения
    bool isEqual(const Hex &other) const;   // Равно
    bool isGreater(const Hex &other) const; // Больше
    bool isLess(const Hex &other) const;    // Меньше

    // Другие методы
    string toString() const;    // Преобразование в строку

private:
    unsigned char* digits; // Динамический массив для хранения цифр
    size_t size;           // Размер массива

    // Вспомогательные методы
    void allocateMemory(size_t newSize); // Выделение памяти
    void copyFrom(const Hex &other);     // Копирование массива
    void freeMemory();                   // Освобождение памяти
};

#endif 
