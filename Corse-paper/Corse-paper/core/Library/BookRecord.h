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
        int documentId = 0;         
        std::string readerCardId;   
        std::time_t issueDate = 0;   
        std::time_t dueDate = 0;     

        /// @brief Формує рядок CSV для збереження транзакції.
        std::string ToCsv() const;

        /// @brief Зчитує дані транзакції з рядка CSV.
        void FromCsv(const std::string& line);
    };
}