#pragma once

#include <string>
#include <iostream>

namespace LibraryCore
{
    /// @brief Клас студента-читача. Зберігає персональні дані та CSV-логіку
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
        /// @brief Конструктор за замовчуванням.
        Student();

        /// @brief Конструктор з повним набором даних.
        Student(
            const std::string& lName,
            const std::string& fName,
            const std::string& recBook,
            int crs,
            const std::string& grp,
            const std::string& cardId
        );

        /// @brief Деструктор.
        ~Student();

        // Копіювання та переміщення
        Student(const Student& other);
        Student& operator=(const Student& other);
        Student(Student&& other) noexcept;
        Student& operator=(Student&& other) noexcept;

        // Get/Set методи
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

        // Основні методи 
 
        /// @brief Повертає повне ім'я (Прізвище + Ім'я)
        std::string GetFullName() const;

        /// @brief Виводить інформацію в консоль.
        void DisplayInfo() const;

        /// @brief Переводить студента на наступний курс.
        void IncrementCourse();

        /**
         * @brief Формує рядок CSV для запису у файл.
         * @param delimiter Розділювач (за замовчуванням ';').
         */
        std::string ToCsv() const;

        /// @brief Заповнює об'єкт з CSV рядка.
        void FromCsv(const std::string& line);
    };
}