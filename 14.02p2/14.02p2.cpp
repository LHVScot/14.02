#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "Phone_book.h"

using namespace std;

int main()
{
    PhoneBook phoneBook;
    string filename = "phonebook.txt";

    while (true) {
        cout << "\nТелефонная книга\n";
        cout << "1. Добавить абонента\n";
        cout << "2. Удалить абонента\n";
        cout << "3. Найти абонента\n";
        cout << "4. Показать всех абонентов\n";
        cout << "5. Сохранить в файл\n";
        cout << "6. Загрузить из файла\n";
        cout << "7. Выйти\n";
        cout << "Выберите действие: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            phoneBook.addEntry();
            break;
        case 2:
            phoneBook.deleteEntry();
            break;
        case 3:
            phoneBook.searchEntry();
            break;
        case 4:
            phoneBook.displayAllEntries();
            break;
        case 5:
            phoneBook.saveToFile(filename);
            break;
        case 6:
            phoneBook.loadFromFile(filename);
            break;
        case 7:
            cout << "Выход из программы.\n";
            return 0;
        default:
            cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
        }
    }
}

