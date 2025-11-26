#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H

#include <string>

namespace LibraryCore {

    /// @enum ValidationMode
    /// @brief Режими перевірки текстового вводу.
    enum class ValidationMode {
        ANY,       
        TEXT_ONLY,  
        DIGITS_ONLY
    };

    /// @class InputValidation
    /// @brief Статичний клас-утиліта для безпечного вводу даних з консолі.
    /// Забезпечує захист від некоректного вводу (наприклад, букв замість цифр),
    /// перевірку діапазонів значень та валідацію формату рядків. 
    class InputValidation {
    public:

        /// @brief Зчитує рядок з консолі з перевіркою вмісту.
        /// @param prompt Текст запитання, який виводиться користувачеві.
        /// @param mode Режим перевірки (ANY, TEXT_ONLY, DIGITS_ONLY).
        /// @return Валідний рядок, введений користувачем.
        static std::string GetStringInput(const std::string& prompt, ValidationMode mode = ValidationMode::ANY);

        /// @brief Зчитує ціле число з перевіркою діапазону.
        /// @param prompt Текст запитання.
        /// @param min Мінімальне допустиме значення.
        /// @param max Максимальне допустиме значення.
        /// @return Валідне ціле число.
        static int GetIntInput(const std::string& prompt, int min = 0, int max = 2147483647);

        /// @brief Зчитує дробове число з перевіркою діапазону.
        /// @param prompt Текст запитання.
        /// @param min Мінімальне допустиме значення.
        /// @param max Максимальне допустиме значення.
        /// @return Валідне дробове число.
        static double GetDoubleInput(const std::string& prompt, double min = 0.0, double max = 1000000.0);
    };
}

#endif