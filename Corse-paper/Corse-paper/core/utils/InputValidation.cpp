#include "InputValidation.h"
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <cctype>   

using namespace std;

namespace LibraryCore {

    // Реалізація методу вводу рядка
    string InputValidation::GetStringInput(const string& prompt, ValidationMode mode)
    {
        while (true)
        {
            cout << prompt << " ";
            string input;
            getline(cin, input);

            if (input.empty()) {
                cout << "Помилка: Поле не може бути порожнім.\n";
                continue;
            }

            bool isValid = true;

            if (mode == ValidationMode::TEXT_ONLY) {
                for (char c : input) {
                    if (!isalpha((unsigned char)c) && c != ' ' && c != '-') {
                        if (isdigit((unsigned char)c) || ispunct((unsigned char)c)) {
                            isValid = false;
                            break;
                        }
                    }
                }
                if (!isValid) {
                    cout << "Помилка: Введіть тільки текст (без цифр).\n";
                    continue;
                }
            }
            else if (mode == ValidationMode::DIGITS_ONLY) {
                for (char c : input) {
                    if (!isdigit((unsigned char)c)) {
                        isValid = false;
                        break;
                    }
                }
                if (!isValid) {
                    cout << "Помилка: Введіть тільки цифри.\n";
                    continue;
                }
            }

            return input;
        }
    }

    // Реалізація методу вводу цілого числа
    int InputValidation::GetIntInput(const string& prompt, int min, int max)
    {
        while (true)
        {
            cout << prompt << " ";
            string input;
            getline(cin, input);

            try {
                size_t pos = 0;
                int value = stoi(input, &pos);

                if (pos != input.length()) { 
                    throw invalid_argument("Помилка: не число");
                }

                if (value < min || value > max) {
                    cout << "Помилка: Число має бути від " << min << " до " << max << ".\n";
                    continue;
                }

                return value;
            }
            catch (...) {
                cout << "Помилка: Введіть коректне ціле число.\n";
            }
        }
    }
    // Реалізація методу вводу дробового числа 
    double InputValidation::GetDoubleInput(const string& prompt, double min, double max)
    {
        while (true)
        {
            cout << prompt << " ";
            string input;
            getline(cin, input);

            try {
                size_t pos = 0;
                double value = stod(input, &pos);

                if (pos != input.length()) {
                    throw invalid_argument("Not a number");
                }

                if (value < min || value > max) {
                    cout << "Помилка: Число має бути від " << min << " до " << max << ".\n";
                    continue;
                }

                return value;
            }
            catch (...) {
                cout << "Помилка: Введіть коректне дробове число.\n";
            }
        }
    }
}