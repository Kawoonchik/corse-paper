#pragma once
#include "Document.h"

namespace LibraryCore
{
    /**
     * @class PrintedDocument
     * @brief Представляє фізичну друковану книгу або інший друкований матеріал.
     *
     * Наслідує Document, додаючи специфічні поля: pageCount та medium.
     */
    class PrintedDocument : public Document
    {
    private:
        int pageCount;
        std::string medium; // Палітурка, журнал тощо

    public:
        /** @brief Конструктор за замовчуванням. */
        PrintedDocument();

        /**
         * @brief Конструктор з параметрами.
         * @param id - Унікальний ідентифікатор документа.
         * @param title - Назва документа.
         * @param author - Автор.
         * @param year - Рік видання.
         * @param pageCount - Кількість сторінок.
         * @param medium - Тип носія (палітурка).
         */
        PrintedDocument(int id, const std::string& title, const std::string& author, int year,
            int pageCount, const std::string& medium);

        virtual ~PrintedDocument();

        PrintedDocument(const PrintedDocument& other);            // Копіювання
        PrintedDocument& operator=(const PrintedDocument& other); // Присвоєння копії
        PrintedDocument(PrintedDocument&& other) noexcept;        // Переміщення
        PrintedDocument& operator=(PrintedDocument&& other) noexcept; // Присвоєння переміщення

        // Get/Set
        /** @brief Встановлює кількість сторінок. @param count - Кількість сторінок. */
        void SetPageCount(int count);
        /** @brief Повертає кількість сторінок. @return Кількість сторінок. */
        int GetPageCount() const;

        /** @brief Встановлює тип носія. @param medium - Тип носія. */
        void SetMedium(const std::string& medium);
        /** @brief Повертає тип носія. @return Тип носія. */
        std::string GetMedium() const;

        // Перевизначені методи
        std::string GetType() const override;
        std::string GetDetails() const override;
        void DisplayInfo() const override;

        std::string ToCsv() const override;
        void FromCsv(const std::string& line) override;
    };
}