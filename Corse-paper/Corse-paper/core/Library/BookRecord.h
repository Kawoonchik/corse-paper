#pragma once
#include <string>
#include <ctime> // Для std::time_t

namespace LibraryCore
{
    struct BookRecord
    {
        int documentId;           // ID книги
        std::string readerCardId; // ID студента
        std::time_t issueDate;    // Дата видачі
        std::time_t dueDate;      // Дата повернення

        // Методи для запису у файл
        std::string ToCsv() const;
        void FromCsv(const std::string& line);
    };
}