#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

class PhoneBookEntry {
private:
    char* fullName; 
    string homePhone;
    string workPhone;
    string mobilePhone;
    string additionalInfo;

public:
    // Конструктор по умолчанию
    PhoneBookEntry() : fullName(nullptr), homePhone(""), workPhone(""), mobilePhone(""), additionalInfo("") {
        cout << "Конструктор по умолчанию вызван" << endl;
    }

    // Конструктор с инициализацией ФИО
    PhoneBookEntry(const char* name) : homePhone(""), workPhone(""), mobilePhone(""), additionalInfo("") {
        cout << "Конструктор с инициализацией ФИО вызван" << endl;
        if (name != nullptr) {
            fullName = new char[strlen(name) + 1];
            strcpy(fullName, name);
        }
        else {
            fullName = nullptr;
        }
    }

    // Конструктор копирования
    PhoneBookEntry(const PhoneBookEntry& other) : homePhone(other.homePhone), workPhone(other.workPhone), mobilePhone(other.mobilePhone), additionalInfo(other.additionalInfo) {
        cout << "Конструктор копирования вызван" << endl;
        if (other.fullName != nullptr) {
            fullName = new char[strlen(other.fullName) + 1];
            strcpy(fullName, other.fullName);
        }
        else {
            fullName = nullptr;
        }
    }

    // Оператор присваивания
    PhoneBookEntry& operator=(const PhoneBookEntry& other) {
        cout << "Оператор присваивания вызван" << endl;
        if (this != &other) { // Проверка на самоприсваивание
            // Освобождаем старую память
            delete[] fullName;

            // Копируем данные
            homePhone = other.homePhone;
            workPhone = other.workPhone;
            mobilePhone = other.mobilePhone;
            additionalInfo = other.additionalInfo;

            if (other.fullName != nullptr) {
                fullName = new char[strlen(other.fullName) + 1];
                strcpy(fullName, other.fullName);
            }
            else {
                fullName = nullptr;
            }
        }
        return *this;
    }

    // Деструктор
    ~PhoneBookEntry() {
        cout << "Деструктор вызван" << endl;
        delete[] fullName;
    }

    // Inline функция для установки ФИО
    inline void setFullName(const char* name) {
        delete[] fullName; // Освобождаем старую память
        if (name != nullptr) {
            fullName = new char[strlen(name) + 1];
            strcpy(fullName, name);
        }
        else {
            fullName = nullptr;
        }
    }

    // Функции для установки других полей
    void setHomePhone(const string& phone) { homePhone = phone; }
    void setWorkPhone(const string& phone) { workPhone = phone; }
    void setMobilePhone(const string& phone) { mobilePhone = phone; }
    void setAdditionalInfo(const string& info) { additionalInfo = info; }

    // Функции для получения данных
    inline const char* getFullName() const { return fullName; } // Inline getter
    const string& getHomePhone() const { return homePhone; }
    const string& getWorkPhone() const { return workPhone; }
    const string& getMobilePhone() const { return mobilePhone; }
    const string& getAdditionalInfo() const { return additionalInfo; }

    // Функция для вывода информации об абоненте
    void display() const {
        cout << "ФИО: " << (fullName != nullptr ? fullName : "Не указано") << endl;
        cout << "Домашний телефон: " << homePhone << endl;
        cout << "Рабочий телефон: " << workPhone << endl;
        cout << "Мобильный телефон: " << mobilePhone << endl;
        cout << "Дополнительная информация: " << additionalInfo << endl;
    }

    // Функция для сохранения данных в файл
    void saveToFile(ofstream& file) const {
        file << (fullName != nullptr ? fullName : "") << endl;
        file << homePhone << endl;
        file << workPhone << endl;
        file << mobilePhone << endl;
        file << additionalInfo << endl;
    }

    // Функция для загрузки данных из файла
    void loadFromFile(ifstream& file) {
        string name;
        getline(file, name);
        setFullName(name.c_str()); // Используем setFullName для правильного выделения памяти

        getline(file, homePhone);
        getline(file, workPhone);
        getline(file, mobilePhone);
        getline(file, additionalInfo);
    }
};

class PhoneBook {
private:
    vector<PhoneBookEntry> entries;

public:
    // Добавление абонента
    void addEntry() {
        PhoneBookEntry entry;

        // Ввод ФИО с динамическим выделением памяти
        string fullNameStr;
        cout << "Введите ФИО: ";
        cin.ignore(); // Очистка буфера после предыдущего ввода
        getline(cin, fullNameStr);
        entry.setFullName(fullNameStr.c_str());

        cout << "Введите домашний телефон: ";
        string homePhone;
        getline(cin, homePhone);
        entry.setHomePhone(homePhone);

        cout << "Введите рабочий телефон: ";
        string workPhone;
        getline(cin, workPhone);
        entry.setWorkPhone(workPhone);

        cout << "Введите мобильный телефон: ";
        string mobilePhone;
        getline(cin, mobilePhone);
        entry.setMobilePhone(mobilePhone);

        cout << "Введите дополнительную информацию: ";
        string additionalInfo;
        getline(cin, additionalInfo);
        entry.setAdditionalInfo(additionalInfo);

        entries.push_back(entry);
        cout << "Абонент добавлен.\n";
    }

    // Удаление абонента по ФИО
    void deleteEntry() {
        string nameToDelete;
        cout << "Введите ФИО абонента для удаления: ";
        cin.ignore();
        getline(cin, nameToDelete);

        bool found = false;
        for (size_t i = 0; i < entries.size(); ++i) {
            if (entries[i].getFullName() != nullptr && string(entries[i].getFullName()) == nameToDelete) {
                entries.erase(entries.begin() + i);
                cout << "Абонент удален.\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Абонент с таким ФИО не найден.\n";
        }
    }

    // Поиск абонента по ФИО
    void searchEntry() {
        string searchName;
        cout << "Введите ФИО абонента для поиска: ";
        cin.ignore();
        getline(cin, searchName);

        bool found = false;
        for (const auto& entry : entries) {
            if (entry.getFullName() != nullptr && string(entry.getFullName()) == searchName) {
                cout << "Найден абонент:\n";
                entry.display();
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Абонент с таким ФИО не найден.\n";
        }
    }

    // Отображение всех абонентов
    void displayAllEntries() {
        if (entries.empty()) {
            cout << "Телефонная книга пуста.\n";
            return;
        }

        cout << "Список абонентов:\n";
        for (const auto& entry : entries) {
            entry.display();
            cout << "----------------------\n";
        }
    }

    // Сохранение в файл
    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            file << entries.size() << endl; // Сохраняем количество записей

            for (const auto& entry : entries) {
                entry.saveToFile(file);
            }

            file.close();
            cout << "Телефонная книга сохранена в файл \"" << filename << "\".\n";
        }
        else {
            cerr << "Не удалось открыть файл для сохранения.\n";
        }
    }

    // Загрузка из файла
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            entries.clear(); // Очищаем текущие записи

            int numEntries;
            file >> numEntries;
            file.ignore(); // Очистка буфера после чтения числа

            for (int i = 0; i < numEntries; ++i) {
                PhoneBookEntry entry;
                entry.loadFromFile(file);
                entries.push_back(entry);
            }

            file.close();
            cout << "Телефонная книга загружена из файла \"" << filename << "\".\n";
        }
        else {
            cerr << "Не удалось открыть файл для загрузки.\n";
        }
    }
};
