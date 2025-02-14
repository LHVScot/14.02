#pragma once
#include <iostream>

using namespace std;

class Fraction {
private:
    int numerator;   // ���������
    int denominator; // �����������

    // ������� ��� ���������� ����������� ������ �������� 
    // ������������ ��� ���������� �����
    int gcd(int a, int b) {
        a = abs(a); // ������������ ������������� ��������
        b = abs(b);
        while (b) {
            a %= b;
            swap(a, b);
        }
        return a;
    }

    // ��������������� ������� ��� ���������� �����
    void reduce() {
        if (denominator == 0) {
            throw invalid_argument("������� �� ����!"); // ��������� ������� �� ����
        }

        if (numerator == 0) {
            denominator = 1;
            return;
        }

        int common = gcd(numerator, denominator);
        numerator /= common;
        denominator /= common;

        // ����������, ��� ����������� ������ �������������
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    // ����������� �� ���������
    Fraction() : numerator(0), denominator(1) {}

    // ����������� � ����������� (���������, �����������)
    Fraction(int num, int den) : numerator(num), denominator(den) {
        if (denominator == 0) {
            throw invalid_argument("������� �� ����!"); // ��������� ������� �� ����
        }
        reduce();
    }

    // ����� ��� ����� ������ 
    void input() {
        cout << "������� ���������: ";
        cin >> numerator;
        do {
            cout << "������� ����������� (�� ����): ";
            cin >> denominator;
            if (denominator == 0) {
                cout << "����������� �� ����� ���� ����� ����. ����������, ������� ������ ��������.\n";
            }
        } while (denominator == 0);
        reduce();
    }

    // ����� ��� ������ ����� � ������� "���������/�����������"
    void output() const {
        if (denominator == 1) {
            cout << numerator; // ���� ����������� 1, ������� ������ ���������
        }
        else {
            cout << numerator << "/" << denominator;
        }
    }

    // �������� ��������
    Fraction operator+(const Fraction& other) const {
        int newNumerator = numerator * other.denominator + other.numerator * denominator;
        int newDenominator = denominator * other.denominator;
        return Fraction(newNumerator, newDenominator);
    }

    // �������� ���������
    Fraction operator-(const Fraction& other) const {
        int newNumerator = numerator * other.denominator - other.numerator * denominator;
        int newDenominator = denominator * other.denominator;
        return Fraction(newNumerator, newDenominator);
    }

    // �������� ���������
    Fraction operator*(const Fraction& other) const {
        int newNumerator = numerator * other.numerator;
        int newDenominator = denominator * other.denominator;
        return Fraction(newNumerator, newDenominator);
    }

    // �������� �������
    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            throw invalid_argument("������� �� ����!");
        }
        int newNumerator = numerator * other.denominator;
        int newDenominator = denominator * other.numerator;
        return Fraction(newNumerator, newDenominator);
    }
};

