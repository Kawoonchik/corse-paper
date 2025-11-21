#pragma once
#include <string>
#include <vector>
#include <iostream>

namespace LibraryCore
{
    /**
     * @class Document
     * @brief Абстрактний базовий клас для всіх матеріалів бібліотеки.
     *
     * Містить спільні поля (ID, назва, автор, рік) та віртуальний інтерфейс
     * для реалізації поліморфізму (GetType, ToCsv, FromCsv).
     */
    class Document
    {
    protected:
        int id;
        std::string title;
        std::string author;
        int year;

    public:
        /**
         * @brief Конструктор за замовчуванням.
         */
        Document();

        /**
         * @brief Конструктор з параметрами.
         * @param id - Унікальний ідентифікатор документа.
         * @param title - Назва документа.
         * @param author - Автор або видавець документа.
         * @param year - Рік видання.
         */
        Document(int id, const std::string& title, const std::string& author, int year);

        /**
         * @brief Віртуальний деструктор.
         * Обов'язковий для коректного видалення об'єктів-нащадків через вказівник на базовий клас.
         */
        virtual ~Document();

        // --- ДОДАНО: Rule of 5 (Вимога 2.3) ---

        // Конструктор копіювання
        Document(const Document& other);
        // Оператор присвоювання копіюванням
        Document& operator=(const Document& other);

        // Конструктор переміщення
        Document(Document&& other) noexcept;
        // Оператор присвоювання переміщенням
        Document& operator=(Document&& other) noexcept;
        // --------------------------------------
        

        // --- Getters / Setters ---
        /** @brief Встановлює унікальний ідентифікатор документа. @param id - Нове значення ID. */
        void SetId(int id);
        /** @brief Повертає унікальний ідентифікатор документа. @return ID документа. */
        int GetId() const;

        /** @brief Встановлює назву документа. @param title - Нова назва. */
        void SetTitle(const std::string& title);
        /** @brief Повертає назву документа. @return Назва документа. */
        std::string GetTitle() const;

        /** @brief Встановлює автора документа. @param author - Новий автор. */
        void SetAuthor(const std::string& author);
        /** @brief Повертає автора документа. @return Автор документа. */
        std::string GetAuthor() const;

        /** @brief Встановлює рік видання. @param year - Новий рік видання. */
        void SetYear(int year);
        /** @brief Повертає рік видання. @return Рік видання. */
        int GetYear() const;

        // --- Віртуальні методи (Interface) ---

        /**
         * @brief Повертає тип документа у вигляді рядка (наприклад, "Printed" або "Electronic").
         * @return Рядок, що ідентифікує тип.
         */
        virtual std::string GetType() const = 0;

        /**
         * @brief Повертає деталі специфічних полів у вигляді форматованого рядка.
         * @return Деталі документа.
         */
        virtual std::string GetDetails() const = 0;

        /**
         * @brief Виводить повну інформацію про документ у консоль.
         */
        virtual void DisplayInfo() const;

        // --- CSV методи ---

        /**
         * @brief Формує CSV рядок, що містить базові поля документа.
         * @return Рядок у форматі ID;Title;Author;Year;...
         */
        virtual std::string ToCsv() const;

        /**
         * @brief Парсить CSV рядок і заповнює базові поля об'єкта.
         * @param line - Вхідний рядок CSV для парсингу.
         */
        virtual void FromCsv(const std::string& line);

    protected:
        /**
         * @brief Розбиває вхідний рядок CSV на токени.
         * @param line - Рядок для розбиття.
         * @param delimiter - Символ-розділювач (за замовчуванням ';').
         * @return Вектор рядків (токенів).
         */
        std::vector<std::string> SplitCsvLine(const std::string& line, char delimiter = ';') const;
    };
}