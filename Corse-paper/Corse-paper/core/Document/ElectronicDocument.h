#pragma once
#include "Document.h"

namespace LibraryCore
{
    /**
     * @class ElectronicDocument
     * @brief Представляє електронну версію документа (файл).
     *
     * Наслідує Document, додаючи специфічні поля: fileFormat та fileSizeMB.
     */
    class ElectronicDocument : public Document
    {
    private:
        std::string fileFormat; // PDF, EPUB, DOC
        double fileSizeMB;      // Розмір файлу в мегабайтах

    public:
        /** @brief Конструктор за замовчуванням. */
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

        virtual ~ElectronicDocument();

        ElectronicDocument(const ElectronicDocument& other);            // Копіювання
        ElectronicDocument& operator=(const ElectronicDocument& other); // Присвоєння копії
        ElectronicDocument(ElectronicDocument&& other) noexcept;        // Переміщення
        ElectronicDocument& operator=(ElectronicDocument&& other) noexcept; // Присвоєння переміщення

        // Get/Set
        /** @brief Встановлює формат файлу. @param format - Новий формат файлу. */
        void SetFileFormat(const std::string& format);
        /** @brief Повертає формат файлу. @return Формат файлу. */
        std::string GetFileFormat() const;

        /** @brief Встановлює розмір файлу. @param size - Розмір файлу у МБ. */
        void SetFileSizeMB(double size);
        /** @brief Повертає розмір файлу. @return Розмір файлу у МБ. */
        double GetFileSizeMB() const;

        // Перевизначені методи
        std::string GetType() const override;
        std::string GetDetails() const override;
        void DisplayInfo() const override;

        std::string ToCsv() const override;
        void FromCsv(const std::string& line) override;
    };
}