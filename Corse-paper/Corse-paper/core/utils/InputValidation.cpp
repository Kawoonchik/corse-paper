#include "InputValidation.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

// ============================================
// 1. Отримання рядкового вводу
// ============================================
string InputValidation::GetStringInput(const string& prompt)
{
    while (true)
    {
        cout << prompt << " ";

        string input;
        getline(cin, input);

        // Перевірка: рядок не має бути пустим
        if (!input.empty())
            return input;

        cout << "Помилка: введено порожній рядок. Спробуйте ще раз.\n";
    }
}

// ============================================
// 2. Перевірка на ціле число
// ============================================
int InputValidation::GetIntInput(const string& prompt)
{
    while (true)
    {
        string s = GetStringInput(prompt);

        try {
            size_t pos = 0;
            int value = stoi(s, &pos);

            if (pos == s.length())  // усі символи були числом
                return value;
        }
        catch (...) {}

        cout << "Помилка: введіть ціле число.\n";
    }
}

// ============================================
// 3. Перевірка на число з плаваючою крапкою
// ============================================
double InputValidation::GetDoubleInput(const string& prompt)
{
    while (true)
    {
        string s = GetStringInput(prompt);

        try {
            size_t pos = 0;
            double value = stod(s, &pos);

            if (pos == s.length())  // повне співпадіння формату
                return value;
        }
        catch (...) {}

        cout << "Помилка: введіть десяткове число.\n";
    }
}
