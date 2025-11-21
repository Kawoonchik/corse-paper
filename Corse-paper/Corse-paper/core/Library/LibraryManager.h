#pragma once

#include "../Student/Student.h"
#include "../Document/Document.h"
#include "../Document/PrintedDocument.h"
#include "../Document/ElectronicDocument.h"
#include "../Users/User.h"
#include "BookRecord.h"

#include <vector>
#include <memory> // Для розумних вказівників (unique_ptr)
#include <ctime>  // Для роботи з датами

namespace LibraryCore
{
    /**
     * @class LibraryManager
     * @brief Центральний клас для управління всіма даними бібліотеки та логікою.
     *
     * Відповідає за CRUD, пошук, сортування, авторизацію та файлові операції.
     */
    class LibraryManager
    {
    private:
        // Використовуємо unique_ptr для безпечного керування поліморфною колекцією
        std::vector<std::unique_ptr<Document>> documents;
        std::vector<Student> students;
        std::vector<User> users;
        std::vector<BookRecord> transactions; // Облік видачі

        // Вказівник на поточного користувача (для авторизації)
        User* currentUser;

        // Допоміжна функція для створення об'єкта Document на основі його типу (для FromCsv)
        std::unique_ptr<Document> CreateDocumentFromCsv(const std::string& line);

    public:
        LibraryManager();
        ~LibraryManager();

        // --- 1. Авторизація та Управління Користувачами (Вимога 1.6) ---

        bool Login(const std::string& username, const std::string& password);
        void Logout();
        User* GetCurrentUser() const;

        bool RegisterUser(const std::string& username, const std::string& password, bool isAdmin = false);
        bool DeleteUser(const std::string& username);
        void DisplayUserList() const;


        // --- 2. Робота з Файлами (Вимога 1.4, 4.x) ---

        void LoadAllData();
        void SaveAllData() const;

        // --- 3. CRUD для Студентів (Вимога 1.5) ---

        void AddStudent(const Student& student);
        void EditStudent(const std::string& cardId, const Student& updatedStudent);
        bool DeleteStudent(const std::string& cardId);
        void DisplayStudents() const;


        // --- 4. CRUD для Документів (Вимога 1.5) ---

        void AddDocument(std::unique_ptr<Document> doc);
        void EditDocument(int id, const Document& updatedDoc);
        bool DeleteDocument(int id);
        void DisplayDocuments() const;


        // --- 5. Основна Бізнес-Логіка (Видача та Облік) ---

        bool CheckoutBook(const std::string& cardId, int documentId);
        bool ReturnBook(const std::string& cardId, int documentId);
        void DisplayDebtorList() const; // Вимога: Список боржників


        // --- 6. Пошук, Сортування, Фільтрація (Вимога 1.5, 2.5) ---

        // Вибір книг за різними критеріями
        std::vector<Document*> SearchDocuments(const std::string& query) const;
        void SortDocumentsByTitle();
        // Фільтрація: повертає список лише надрукованих або лише електронних
        std::vector<Document*> FilterDocumentsByType(const std::string& type) const;
    };
}