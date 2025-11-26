#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H

#include <string>

namespace LibraryCore {

    // Режими перевірки тексту
    enum class ValidationMode {
        ANY,        // Дозволено все (наприклад, для назви книги "C++ 17")
        TEXT_ONLY,  // Тільки букви та пробіли (для Імені, Прізвища)
        DIGITS_ONLY // Тільки цифри (для рядкових ID, якщо треба)
    };

    class InputValidation {
    public:
        // Статичні методи - викликаємо як InputValidation::Method()

        // Додали параметр mode для перевірки типу символів
        static std::string GetStringInput(const std::string& prompt, ValidationMode mode = ValidationMode::ANY);

        // Додали min/max для чисел
        static int GetIntInput(const std::string& prompt, int min = 0, int max = 2147483647);

        static double GetDoubleInput(const std::string& prompt, double min = 0.0, double max = 1000000.0);
    };
}

#endif