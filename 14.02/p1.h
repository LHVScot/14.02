#pragma once
#include <iostream>

using namespace std;

class Fraction {
private:
    int numerator;   // Числитель
    int denominator; // Знаменатель

    // Функция для нахождения наибольшего общего делителя 
    // Используется для сокращения дроби
    int gcd(int a, int b) {
        a = abs(a); // Обрабатываем отрицательные значения
        b = abs(b);
        while (b) {
            a %= b;
            swap(a, b);
        }
        return a;
    }

    // Вспомогательная функция для сокращения дроби
    void reduce() {
        if (denominator == 0) {
            throw invalid_argument("Деление на ноль!"); // Обработка деления на ноль
        }

        if (numerator == 0) {
            denominator = 1;
            return;
        }

        int common = gcd(numerator, denominator);
        numerator /= common;
        denominator /= common;

        // Убеждаемся, что знаменатель всегда положительный
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    // Конструктор по умолчанию
    Fraction() : numerator(0), denominator(1) {}

    // Конструктор с параметрами (числитель, знаменатель)
    Fraction(int num, int den) : numerator(num), denominator(den) {
        if (denominator == 0) {
            throw invalid_argument("Деление на ноль!"); // Обработка деления на ноль
        }
        reduce();
    }

    // Метод для ввода данных 
    void input() {
        cout << "Введите числитель: ";
        cin >> numerator;
        do {
            cout << "Введите знаменатель (не ноль): ";
            cin >> denominator;
            if (denominator == 0) {
                cout << "Знаменатель не может быть равен нулю. Пожалуйста, введите другое значение.\n";
            }
        } while (denominator == 0);
        reduce();
    }

    // Метод для вывода дроби в формате "числитель/знаменатель"
    void output() const {
        if (denominator == 1) {
            cout << numerator; // Если знаменатель 1, выводим только числитель
        }
        else {
            cout << numerator << "/" << denominator;
        }
    }

    // Оператор сложения
    Fraction operator+(const Fraction& other) const {
        int newNumerator = numerator * other.denominator + other.numerator * denominator;
        int newDenominator = denominator * other.denominator;
        return Fraction(newNumerator, newDenominator);
    }

    // Оператор вычитания
    Fraction operator-(const Fraction& other) const {
        int newNumerator = numerator * other.denominator - other.numerator * denominator;
        int newDenominator = denominator * other.denominator;
        return Fraction(newNumerator, newDenominator);
    }

    // Оператор умножения
    Fraction operator*(const Fraction& other) const {
        int newNumerator = numerator * other.numerator;
        int newDenominator = denominator * other.denominator;
        return Fraction(newNumerator, newDenominator);
    }

    // Оператор деления
    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            throw invalid_argument("Деление на ноль!");
        }
        int newNumerator = numerator * other.denominator;
        int newDenominator = denominator * other.numerator;
        return Fraction(newNumerator, newDenominator);
    }
};

