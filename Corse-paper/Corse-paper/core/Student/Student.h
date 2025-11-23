#pragma once

#include <string>
#include <iostream>

#include "../utils/ISerializable.h"


namespace LibraryCore
{
    /**
    * @class Student
    * @brief Клас студента-читача.
    * * Зберігає персональні дані студента, інформацію про курс та групу,
    * а також реалізує логіку серіалізації у формат CSV.
    */
	class Student : public ISerializable
    {
    private:
        std::string lastName;
        std::string firstName;
        std::string recordBookNumber;
        int course;
        std::string group;
        std::string readerCardId;

    public:
        /**
        * @brief Конструктор за замовчуванням.
        */
        Student();

         /**
         * @brief Конструктор з повним набором даних.
         * @param lName Прізвище.
         * @param fName Ім'я.
         * @param recBook Номер залікової книжки.
         * @param crs Курс (1-6).
         * @param grp Група.
         * @param cardId Номер читацького квитка (унікальний ID).
         */
        Student(
            const std::string& lName,
            const std::string& fName,
            const std::string& recBook,
            int crs,
            const std::string& grp,
            const std::string& cardId
        );

         /**
         * @brief Деструктор класу.
         */
        ~Student();

        // Копіювання та переміщення

        /** @brief Конструктор копіювання. */
        Student(const Student& other);

        /** @brief Оператор присвоєння копіюванням. */
        Student& operator=(const Student& other);

        /** @brief Конструктор переміщення. */
        Student(Student&& other) noexcept;

        /** @brief Оператор присвоєння переміщенням. */
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
 
         /**
         * @brief Повертає повне ім'я студента.
         * @return Рядок у форматі "Прізвище Ім'я".
         */
        std::string GetFullName() const;

         /**
         * @brief Виводить детальну інформацію про студента в консоль.
         */
        void DisplayInfo() const;

         /**
         * @brief Переводить студента на наступний курс (якщо курс < 6).
         */
        void IncrementCourse();

        /**
         * @brief Формує рядок CSV для запису у файл.
         * @param delimiter Розділювач (за замовчуванням ';').
         */
        std::string ToCsv() const override;

         /**
         * @brief Заповнює поля об'єкта даними з CSV рядка.
         * @param line Вхідний рядок з файлу.
         */
        void FromCsv(const std::string& line) override;
    };
}