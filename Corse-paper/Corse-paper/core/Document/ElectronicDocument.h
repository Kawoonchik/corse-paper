#pragma once
#include "Document.h"


namespace LibraryCore
{
     /**
     * @class ElectronicDocument
     * @brief Клас для електронних файлів.
     * * Нащадок класу Document. Додає поля для формату файлу та його розміру.
     */
    class ElectronicDocument : public Document
    {
    private:
        std::string fileFormat;
        double fileSizeMB; 

    public:
            /**
         * @brief Конструктор за замовчуванням.
         */
        ElectronicDocument();

        /**
         * @brief Конструктор з параметрами.
         * @param id - Унікальний ідентифікатор документа.
         * @param title - Назва документа.
         * @param author - Автор.
         * @param year - Рік видання.
         * @param format - Формат електронного файлу (наприклад, "PDF").
         * @param size - Розмір файлу у мегабайтах.
         */
        ElectronicDocument(int id, const std::string& title, const std::string& author, int year,
            const std::string& format, double size);

        /**
         * @brief Деструктор.
         */
        virtual ~ElectronicDocument();

        // Копіювання та переміщення

        /** @brief Конструктор копіювання. */
        ElectronicDocument(const ElectronicDocument& other);

        /** @brief Оператор присвоєння копіюванням. */
        ElectronicDocument& operator=(const ElectronicDocument& other);

        /** @brief Конструктор переміщення. */
        ElectronicDocument(ElectronicDocument&& other) noexcept;

        /** @brief Оператор присвоєння переміщенням. */
        ElectronicDocument& operator=(ElectronicDocument&& other) noexcept;

        // Get/Set методи

        void SetFileFormat(const std::string& format);
        std::string GetFileFormat() const;

        void SetFileSizeMB(double size);
        double GetFileSizeMB() const;

        // Перевизначені методи

        /**
         * @brief Повертає тип "Electronic".
         */
        std::string GetType() const override;

        /**
         * @brief Повертає рядок "Формат, X MB".
         */
        std::string GetDetails() const override;

        /**
         * @brief Виводить інформацію про електронний файл.
         */
        void DisplayInfo() const override;

        /**
         * @brief Додає специфічні поля до CSV рядка.
         */
        std::string ToCsv() const override;

        /**
         * @brief Зчитує специфічні поля з CSV рядка.
         */
        void FromCsv(const std::string& line) override;
    };
}