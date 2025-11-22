#pragma once

#include "../Student/Student.h"
#include "../Document/Document.h"
#include "../Document/PrintedDocument.h"
#include "../Document/ElectronicDocument.h"
#include "../Users/User.h"
#include "BookRecord.h"

#include <vector>
#include <memory>
#include <ctime> 

namespace LibraryCore
{
     /**
     * @class LibraryManager
     * @brief Головний клас-менеджер (Controller).
     * * Цей клас реалізується для роботи з бібліотекою.
     * Він керує колекціями студентів, документів та користувачів,
     * відповідає за збереження даних у файли та логіку.
     */
    class LibraryManager
    {
    private:
        std::vector<std::unique_ptr<Document>> documents;
        std::vector<Student> students;
        std::vector<User> users;
        std::vector<BookRecord> transactions;

        User* currentUser; // Поточний авторизований користувач

         /**
         * @brief Метод для створення документа з CSV рядка.
         * Визначає тип документа ("Printed" чи "Electronic") і створює відповідний об'єкт.
         */
        std::unique_ptr<Document> CreateDocumentFromCsv(const std::string& line);

    public:

        /**
         * @brief Конструктор. Завантажує всі дані з файлів при запуску.
         */
        LibraryManager();

        /**
         * @brief Деструктор. Зберігає всі дані у файли при виході.
         */
        ~LibraryManager();

        // Авторизація та управління користувачами

         /**
         * @brief Спроба входу в систему.
         * @param username Логін.
         * @param password Пароль.
         * @return true, якщо вхід успішний.
         */
        bool Login(const std::string& username, const std::string& password);

        /**
         * @brief Вихід з системи (розлогінення).
         */
        void Logout();

        /**
         * @brief Повертає вказівник на поточного користувача.
         */
        User* GetCurrentUser() const;

        // Функції адміністратора

        /**
         * @brief Реєстрація нового користувача системи.
         * @param isAdmin - Чи має новий користувач права адміністратора.
         */
        bool RegisterUser(const std::string& username, const std::string& password, bool isAdmin = false);

        /**
         * @brief Видалення користувача за логіном.
         */
        bool DeleteUser(const std::string& username);

        /**
         * @brief Вивід списку всіх користувачів (тільки для адміна).
         */
        void DisplayUserList() const;


        // Робота з Файлами

        /**
         * @brief Завантажує студентів, документи та транзакції з файлів.
         */
        void LoadAllData();

        /**
         * @brief Зберігає поточний стан системи у файли.
         */
        void SaveAllData() const;

        // Управління студентами

        /**
         * @brief Додає нового студента до бази.
         */
        void AddStudent(const Student& student);

        /**
         * @brief Редагує дані існуючого студента.
         * @param cardId ID картки студента, якого редагуємо.
         * @param updatedStudent Об'єкт з новими даними.
         */
        void EditStudent(const std::string& cardId, const Student& updatedStudent);

        /**
         * @brief Видаляє студента з бази (якщо він не боржник).
         */
        bool DeleteStudent(const std::string& cardId);

        /**
         * @brief Виводить список всіх студентів.
         */
        void DisplayStudents() const;


        // Управління документами

        /**
         * @brief Додає новий документ (книгу або файл).
         * @param doc Унікальний вказівник на документ.
         */
        void AddDocument(std::unique_ptr<Document> doc);

        /**
        * @brief Редагує базові дані документа.
        */
        void EditDocument(int id, const Document& updatedDoc); 
        
        /**
         * @brief Видаляє документ (якщо він не виданий).
         */
        bool DeleteDocument(int id);
        
        /**
         * @brief Виводить список всіх документів.
         */
        void DisplayDocuments() const;


        // Видача та Облік

         /**
         * @brief Видача книги студенту.
         * @return true, якщо видача успішна.
         */
        bool CheckoutBook(const std::string& cardId, int documentId);

        /**
         * @brief Повернення книги студентом.
         * @return true, якщо книгу успішно повернено.
         */
        bool ReturnBook(const std::string& cardId, int documentId);

        /**
         * @brief Виводить список боржників (хто прострочив повернення).
         */
        void DisplayDebtorList() const;


        // Пошук, сортування, фільтрація

        /**
         * @brief Пошук документів за назвою або автором.
         * @param query Рядок пошуку.
         * @return Вектор вказівників на знайдені документи.
         */
        std::vector<Document*> SearchDocuments(const std::string& query) const;

        /**
         * @brief Сортує список документів за алфавітом (за назвою).
         */
        void SortDocumentsByTitle();

        /**
         * @brief Фільтрує документи за типом.
         * @param type Тип документа ("Printed" або "Electronic").
         */
        std::vector<Document*> FilterDocumentsByType(const std::string& type) const;
    };
}