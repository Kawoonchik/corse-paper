#pragma once
#include "Document.h"

namespace LibraryCore
{
    /// @class PrintedDocument
    /// @brief Клас для друкованих книг.
    /// Нащадок класу Document. Додає поля для кількості сторінок та типу палітурки.
    class PrintedDocument : public Document
    {
    private:
        int pageCount;
        std::string medium; 

    public:
        /// @brief Конструктор за замовчуванням.
        PrintedDocument();

        /// @brief Конструктор з параметрами.
        /// @param id - Унікальний ідентифікатор документа.
        /// @param title - Назва документа.
        /// @param author - Автор.
        /// @param year - Рік видання.
        /// @param pageCount - Кількість сторінок.
        /// @param medium - Тип носія (палітурка).
        PrintedDocument(int id, const std::string& title, const std::string& author, int year,
            int pageCount, const std::string& medium);

        /// @brief Деструктор.
        virtual ~PrintedDocument();

        // Копіювання та переміщення

        /// @brief Конструктор копіювання.
        PrintedDocument(const PrintedDocument& other);

        /// @brief Оператор присвоєння копіюванням.
        PrintedDocument& operator=(const PrintedDocument& other);

        /// @brief Конструктор переміщення.
        PrintedDocument(PrintedDocument&& other) noexcept;

        /// @brief Оператор присвоєння переміщенням.
        PrintedDocument& operator=(PrintedDocument&& other) noexcept;

        // Get/Set методи

        void SetPageCount(int count);
        int GetPageCount() const;

        void SetMedium(const std::string& medium);
        std::string GetMedium() const;

        // Перевизначені методи

        /// @brief Повертає тип "Printed".
        std::string GetType() const override;

        /// @brief Повертає рядок "N сторінок, Тип палітурки".
        std::string GetDetails() const override;

        /// @brief Виводить інформацію про друковану книгу.
        void DisplayInfo() const override;

        /// @brief Додає специфічні поля до CSV рядка.
        std::string ToCsv() const override;

        /// @brief Зчитує специфічні поля з CSV рядка.
        void FromCsv(const std::string& line) override;
    };
}