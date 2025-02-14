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
    // ����������� �� ���������
    PhoneBookEntry() : fullName(nullptr), homePhone(""), workPhone(""), mobilePhone(""), additionalInfo("") {
        cout << "����������� �� ��������� ������" << endl;
    }

    // ����������� � �������������� ���
    PhoneBookEntry(const char* name) : homePhone(""), workPhone(""), mobilePhone(""), additionalInfo("") {
        cout << "����������� � �������������� ��� ������" << endl;
        if (name != nullptr) {
            fullName = new char[strlen(name) + 1];
            strcpy(fullName, name);
        }
        else {
            fullName = nullptr;
        }
    }

    // ����������� �����������
    PhoneBookEntry(const PhoneBookEntry& other) : homePhone(other.homePhone), workPhone(other.workPhone), mobilePhone(other.mobilePhone), additionalInfo(other.additionalInfo) {
        cout << "����������� ����������� ������" << endl;
        if (other.fullName != nullptr) {
            fullName = new char[strlen(other.fullName) + 1];
            strcpy(fullName, other.fullName);
        }
        else {
            fullName = nullptr;
        }
    }

    // �������� ������������
    PhoneBookEntry& operator=(const PhoneBookEntry& other) {
        cout << "�������� ������������ ������" << endl;
        if (this != &other) { // �������� �� ����������������
            // ����������� ������ ������
            delete[] fullName;

            // �������� ������
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

    // ����������
    ~PhoneBookEntry() {
        cout << "���������� ������" << endl;
        delete[] fullName;
    }

    // Inline ������� ��� ��������� ���
    inline void setFullName(const char* name) {
        delete[] fullName; // ����������� ������ ������
        if (name != nullptr) {
            fullName = new char[strlen(name) + 1];
            strcpy(fullName, name);
        }
        else {
            fullName = nullptr;
        }
    }

    // ������� ��� ��������� ������ �����
    void setHomePhone(const string& phone) { homePhone = phone; }
    void setWorkPhone(const string& phone) { workPhone = phone; }
    void setMobilePhone(const string& phone) { mobilePhone = phone; }
    void setAdditionalInfo(const string& info) { additionalInfo = info; }

    // ������� ��� ��������� ������
    inline const char* getFullName() const { return fullName; } // Inline getter
    const string& getHomePhone() const { return homePhone; }
    const string& getWorkPhone() const { return workPhone; }
    const string& getMobilePhone() const { return mobilePhone; }
    const string& getAdditionalInfo() const { return additionalInfo; }

    // ������� ��� ������ ���������� �� ��������
    void display() const {
        cout << "���: " << (fullName != nullptr ? fullName : "�� �������") << endl;
        cout << "�������� �������: " << homePhone << endl;
        cout << "������� �������: " << workPhone << endl;
        cout << "��������� �������: " << mobilePhone << endl;
        cout << "�������������� ����������: " << additionalInfo << endl;
    }

    // ������� ��� ���������� ������ � ����
    void saveToFile(ofstream& file) const {
        file << (fullName != nullptr ? fullName : "") << endl;
        file << homePhone << endl;
        file << workPhone << endl;
        file << mobilePhone << endl;
        file << additionalInfo << endl;
    }

    // ������� ��� �������� ������ �� �����
    void loadFromFile(ifstream& file) {
        string name;
        getline(file, name);
        setFullName(name.c_str()); // ���������� setFullName ��� ����������� ��������� ������

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
    // ���������� ��������
    void addEntry() {
        PhoneBookEntry entry;

        // ���� ��� � ������������ ���������� ������
        string fullNameStr;
        cout << "������� ���: ";
        cin.ignore(); // ������� ������ ����� ����������� �����
        getline(cin, fullNameStr);
        entry.setFullName(fullNameStr.c_str());

        cout << "������� �������� �������: ";
        string homePhone;
        getline(cin, homePhone);
        entry.setHomePhone(homePhone);

        cout << "������� ������� �������: ";
        string workPhone;
        getline(cin, workPhone);
        entry.setWorkPhone(workPhone);

        cout << "������� ��������� �������: ";
        string mobilePhone;
        getline(cin, mobilePhone);
        entry.setMobilePhone(mobilePhone);

        cout << "������� �������������� ����������: ";
        string additionalInfo;
        getline(cin, additionalInfo);
        entry.setAdditionalInfo(additionalInfo);

        entries.push_back(entry);
        cout << "������� ��������.\n";
    }

    // �������� �������� �� ���
    void deleteEntry() {
        string nameToDelete;
        cout << "������� ��� �������� ��� ��������: ";
        cin.ignore();
        getline(cin, nameToDelete);

        bool found = false;
        for (size_t i = 0; i < entries.size(); ++i) {
            if (entries[i].getFullName() != nullptr && string(entries[i].getFullName()) == nameToDelete) {
                entries.erase(entries.begin() + i);
                cout << "������� ������.\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "������� � ����� ��� �� ������.\n";
        }
    }

    // ����� �������� �� ���
    void searchEntry() {
        string searchName;
        cout << "������� ��� �������� ��� ������: ";
        cin.ignore();
        getline(cin, searchName);

        bool found = false;
        for (const auto& entry : entries) {
            if (entry.getFullName() != nullptr && string(entry.getFullName()) == searchName) {
                cout << "������ �������:\n";
                entry.display();
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "������� � ����� ��� �� ������.\n";
        }
    }

    // ����������� ���� ���������
    void displayAllEntries() {
        if (entries.empty()) {
            cout << "���������� ����� �����.\n";
            return;
        }

        cout << "������ ���������:\n";
        for (const auto& entry : entries) {
            entry.display();
            cout << "----------------------\n";
        }
    }

    // ���������� � ����
    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            file << entries.size() << endl; // ��������� ���������� �������

            for (const auto& entry : entries) {
                entry.saveToFile(file);
            }

            file.close();
            cout << "���������� ����� ��������� � ���� \"" << filename << "\".\n";
        }
        else {
            cerr << "�� ������� ������� ���� ��� ����������.\n";
        }
    }

    // �������� �� �����
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            entries.clear(); // ������� ������� ������

            int numEntries;
            file >> numEntries;
            file.ignore(); // ������� ������ ����� ������ �����

            for (int i = 0; i < numEntries; ++i) {
                PhoneBookEntry entry;
                entry.loadFromFile(file);
                entries.push_back(entry);
            }

            file.close();
            cout << "���������� ����� ��������� �� ����� \"" << filename << "\".\n";
        }
        else {
            cerr << "�� ������� ������� ���� ��� ��������.\n";
        }
    }
};
