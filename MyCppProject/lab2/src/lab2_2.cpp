#include "../include/lab2_2.h"
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

// Конструктор по умолчанию
Hex::Hex() : digits(nullptr), size(0) {}

// Конструктор из строки
Hex::Hex(const string &hexStr) {
    this->size = hexStr.size();
    this->allocateMemory(this->size);
    for (size_t i = 0; i < this->size; ++i) {
        this->digits[i] = static_cast<unsigned char>(stoi(hexStr.substr(i, 1), nullptr, 16));
    }
}

// Конструктор копирования
Hex::Hex(const Hex &other) {
    this->copyFrom(other);
}

// Конструктор перемещения
Hex::Hex(Hex &&other) noexcept : digits(other.digits), size(other.size) {
    other.digits = nullptr;
    other.size = 0;
}

// Деструктор
Hex::~Hex() {
    this->freeMemory();
}

// Методы присваивания
void Hex::assign(const Hex &other) {
    if (this != &other) {
        this->freeMemory();
        this->copyFrom(other);
    }
}

void Hex::assignMove(Hex &&other) noexcept {
    if (this != &other) {
        this->freeMemory();
        this->digits = other.digits;
        this->size = other.size;
        other.digits = nullptr;
        other.size = 0;
    }
}

// Арифметические операции
void Hex::add(const Hex &other) {
    size_t maxSize = std::max(this->size, other.size);
    unsigned char* resultDigits = new unsigned char[maxSize + 1](); 
    unsigned char carry = 0;

    for (size_t i = 0; i < maxSize || carry; ++i) {
        unsigned char digit1 = (i < this->size) ? this->digits[this->size - 1 - i] : 0;
        unsigned char digit2 = (i < other.size) ? other.digits[other.size - 1 - i] : 0; 
        unsigned char sum = digit1 + digit2 + carry; 
        resultDigits[maxSize - i] = sum % 16; 
        carry = sum / 16; 
    }

    delete[] this->digits; 

    if (carry) {
        this->digits = new unsigned char[maxSize + 1]; 
        this->digits[0] = 1; 
        std::copy(resultDigits, resultDigits + maxSize, this->digits + 1);
        this->size = maxSize + 1; 
    } else {
        this->digits = new unsigned char[maxSize]; 
        std::copy(resultDigits + 1, resultDigits + maxSize + 1, this->digits); 
        this->size = maxSize;
    }

    delete[] resultDigits; 
}

void Hex::subtract(const Hex &other) {
    if (this->isLess(other)) {
        throw std::invalid_argument("Результат вычитания отрицателен.");
    }

    size_t maxSize = std::max(this->size, other.size);
    unsigned char* resultDigits = new unsigned char[maxSize]();
    unsigned char borrow = 0;
    for (size_t i = 0; i < maxSize; ++i) {
        unsigned char digit1 = (i < this->size) ? this->digits[this->size - 1 - i] : 0; 
        unsigned char digit2 = (i < other.size) ? other.digits[other.size - 1 - i] : 0; 
        if (digit1 >= digit2 + borrow) {
            resultDigits[maxSize - 1 - i] = digit1 - (digit2 + borrow);
            borrow = 0; 
        } else {
            resultDigits[maxSize - 1 - i] = digit1 + 16 - (digit2 + borrow); 
            borrow = 1; 
        }
    }
    delete[] this->digits; 
    this->digits = resultDigits;
    this->size = maxSize; 
}

// Операции сравнения
bool Hex::isEqual(const Hex &other) const {
    if (this->size != other.size) return false;
    for (size_t i = 0; i < this->size; ++i) {
        if (this->digits[i] != other.digits[i]) return false;
    }
    return true;
}

bool Hex::isGreater(const Hex &other) const {
    if (this->size != other.size) return this->size > other.size;
    for (int i = this->size - 1; i >= 0; --i) {
        if (this->digits[i] > other.digits[i]) return true;
        if (this->digits[i] < other.digits[i]) return false;
    }
    return false;
}

bool Hex::isLess(const Hex &other) const {
    return !this->isGreater(other) && !this->isEqual(other);
}

// Преобразование в строку
std::string Hex::toString() const {
    if (this->size == 0) return "0"; 

    std::ostringstream oss;
    for (size_t i = 0; i < this->size; ++i) {
        oss << std::hex << std::uppercase << static_cast<int>(this->digits[i]);
    }

    std::string result = oss.str();
    
    // Удаляем ведущие нули
    size_t pos = result.find_first_not_of('0');
    if (pos != std::string::npos) {
        return result.substr(pos); // Возвращаем строку без ведущих нулей
    }
    
    return "0"; // Если все символы - нули
}

// Вспомогательные методы
void Hex::allocateMemory(size_t newSize) {
    this->digits = new unsigned char[newSize]();
}

void Hex::copyFrom(const Hex &other) {
    if (this != &other) { 
        delete[] this->digits; 
        this->size = other.size; 
        this->allocateMemory(this->size); 
        for (size_t i = 0; i < this->size; ++i) {
            this->digits[i] = other.digits[i];
        }
    }
}

void Hex::freeMemory() {
    delete[] this->digits;
    this->digits = nullptr;
    this->size = 0;
}