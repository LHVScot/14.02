#include <iostream>
#include "p1.h"

using namespace std;


int main() {
    setlocale(LC_ALL, "ru");
    Fraction fraction1;
    Fraction fraction2;

    cout << "Введите первую дробь:\n";
    fraction1.input();

    cout << "Введите вторую дробь:\n";
    fraction2.input();

    cout << "Первая дробь: ";
    fraction1.output();
    cout << endl;
    cout << "Вторая дробь: ";
    fraction2.output();
    cout << endl;

    // Арифметические операции
    cout << "Сумма: ";
    (fraction1 + fraction2).output();
    cout << endl;

    cout << "Разность: ";
    (fraction1 - fraction2).output();
    cout << endl;

    cout << "Произведение: ";
    (fraction1 * fraction2).output();
    cout << endl;

    try {
        cout << "Частное: ";
        (fraction1 / fraction2).output();
        cout << endl;
    }
    catch (const invalid_argument& e) {
        cerr << "Ошибка: " << e.what() << endl; // Обработка деления на ноль
    }




    return 0;
}