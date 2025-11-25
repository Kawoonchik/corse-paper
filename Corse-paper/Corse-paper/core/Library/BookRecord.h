#pragma once
#include <string>
#include <ctime>

namespace LibraryCore
{
    /// @struct BookRecord
    /// @brief Структура для обліку видачі книг.
    /// * Зв'язує ID документа з читацьким квитком студента та фіксує дати.
    struct BookRecord
    {
        int documentId = 0;           ///< ID виданого документа
        std::string readerCardId;     ///< Номер читацького квитка студента
        std::time_t issueDate = 0;    ///< Дата видачі
        std::time_t dueDate = 0;      ///< Дата, до якої треба повернути

        /// @brief Формує рядок CSV для збереження транзакції.
        std::string ToCsv() const;

        /// @brief Зчитує дані транзакції з рядка CSV.
        void FromCsv(const std::string& line);
    };
}