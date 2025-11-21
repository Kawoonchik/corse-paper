#pragma once // Заміна ifndef/define для сучасності, працює всюди

#include <string>
#include <iostream>

namespace LibraryCore
{
    /**
     * @class Student
     * @brief Клас для зберігання та управління даними про студента.
     * * Реалізовано на стандартному C++ для консольного додатку.
     * Формат збереження даних: CSV.
     */
    class Student
    {
    private:
        std::string lastName;
        std::string firstName;
        std::string recordBookNumber;
        int course;
        std::string group;
        std::string readerCardId;

    public:
        // --- 1. Конструктори та деструктор (Вимога 2.3) ---

        // Конструктор за замовчуванням
        Student();

        // Конструктор з параметрами
        Student(
            const std::string& lName,
            const std::string& fName,
            const std::string& recBook,
            int crs,
            const std::string& grp,
            const std::string& cardId
        );

        // Деструктор (віртуальний не обов'язково, бо від Student не спадкуємось, але з повідомленням)
        ~Student();

        // Конструктор копіювання
        Student(const Student& other);

        // Оператор присвоювання копіюванням
        Student& operator=(const Student& other);

        // Конструктор переміщення
        Student(Student&& other) noexcept;

        // Оператор присвоювання переміщенням
        Student& operator=(Student&& other) noexcept;

        // --- 2. Get/Set методи (Вимога 2.3) ---

        void SetLastName(const std::string& lastName);
        std::string GetLastName() const;

        void SetFirstName(const std::string& firstName);
        std::string GetFirstName() const;

        void SetRecordBookNumber(const std::string& recordBookNumber);
        std::string GetRecordBookNumber() const;

        void SetCourse(int course);
        int GetCourse() const;

        void SetGroup(const std::string& group);
        std::string GetGroup() const;

        void SetReaderCardId(const std::string& readerCardId);
        std::string GetReaderCardId() const;

        // --- 3. Власні методи (Вимога 2.3) ---

        /**
         * @brief Повертає повне ім'я (Прізвище + Ім'я).
         */
        std::string GetFullName() const;

        /**
         * @brief Виводить форматовану інформацію в cout.
         */
        void DisplayInfo() const;

        /**
         * @brief Збільшує курс на 1 (макс 6).
         */
        void IncrementCourse();

        /**
         * @brief Формує рядок CSV для запису у файл.
         * @param delimiter Розділювач (за замовчуванням ';', бо коми можуть бути в тексті).
         */
        std::string ToCsv() const;

        /**
         * @brief Парсить рядок CSV і заповнює поля об'єкта.
         */
        void FromCsv(const std::string& line);
    };
}