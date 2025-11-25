#pragma once
#include <string>

namespace LibraryCore
{
    /// @interface ISerializable
    /// @brief Інтерфейс для об'єктів, які можна зберегти у файл та завантажити з нього.
    /// Містить чисті віртуальні методи для роботи з форматом CSV.
    class ISerializable
    {
    public:
        /// @brief Віртуальний деструктор.
        virtual ~ISerializable() = default;

        /// @brief Перетворити об'єкт у рядок CSV.
        /// @return Рядок з даними.
        virtual std::string ToCsv() const = 0;

        /// @brief Заповнити об'єкт даними з рядка CSV.
        /// @param line Рядок з даними.
        virtual void FromCsv(const std::string& line) = 0;
    };
}
