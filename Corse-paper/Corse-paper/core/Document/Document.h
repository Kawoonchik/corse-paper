#pragma once
#include <string>
#include <vector>
#include <iostream>

#include "../utils/ISerializable.h"

namespace LibraryCore
{
    /// @class Document
    /// @brief Абстрактний базовий клас для всіх матеріалів бібліотеки.
	class Document : public ISerializable
    {
    protected:
        int id;
        std::string title;
        std::string author;
        int year;

    public:

        ///@brief Конструктор за замовчуванням.
        Document();

        /// @brief Конструктор з параметрами.
        /// @param id - Унікальний ідентифікатор документа.
        /// @param title - Назва документа.
        /// @param author - Автор або видавець документа.
        /// @param year - Рік видання.
        Document(int id, const std::string& title, const std::string& author, int year);

        /// @brief Віртуальний деструктор.
        /// Необхідний для коректного видалення об'єктів-нащадків.
        virtual ~Document();

        // Копіювання та переміщення

        /// @brief Конструктор копіювання. 
        Document(const Document& other);

        /// @brief Оператор присвоєння копіюванням.
        Document& operator=(const Document& other);

        /// @brief Конструктор переміщення. 
        Document(Document&& other) noexcept;

        /// @brief Оператор присвоєння переміщенням.
        Document& operator=(Document&& other) noexcept;
        

        // Get / Set методи
        void SetId(int id);
        int GetId() const;

        void SetTitle(const std::string& title);
        std::string GetTitle() const;

        void SetAuthor(const std::string& author);
        std::string GetAuthor() const;

        void SetYear(int year);
        int GetYear() const;

        // Віртуальні методи (Interface)

        /// @brief Повертає тип документа.
        /// @return Рядок "Printed" або "Electronic".
        virtual std::string GetType() const = 0;

        /// @brief Повертає специфічні деталі документа.
        /// @return Рядок з інформацією про сторінки або розмір файлу.
        virtual std::string GetDetails() const = 0;

        /// @brief Виводить повну інформацію про документ у консоль.
        /// Це віртуальний метод, який може бути розширений у нащадках.
        virtual void DisplayInfo() const;

        // CSV методи 

        /// @brief Формує базову частину CSV рядка.
        /// @return Рядок "ID;Title;Author;Year".
        std::string ToCsv() const override;

        /// @brief Зчитує базові поля з CSV рядка.
        /// @param line Вхідний рядок.
        void FromCsv(const std::string& line) override;

    protected:
        /// @brief Розбиває вхідний рядок CSV на токени.
        /// @param line - Рядок для розбиття.
        /// @param delimiter - Символ-розділювач (за замовчуванням ';').
        /// @return Вектор рядків (токенів).
        std::vector<std::string> SplitCsvLine(const std::string& line, char delimiter = ';') const;
    };
}