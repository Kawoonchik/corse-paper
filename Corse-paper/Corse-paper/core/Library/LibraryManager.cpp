#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <algorithm> // Для std::find_if, std::sort
#include <ctime>     // Для time()
#include "LibraryManager.h"

namespace
{
    // Назви файлів для збереження даних
    const std::string STUDENTS_FILE = "students.txt";
    const std::string DOCUMENTS_FILE = "documents.txt";
    const std::string USERS_FILE = "users.txt";
    const std::string TRANSACTIONS_FILE = "transactions.txt";
}

using namespace LibraryCore;
using std::string;
using std::cout;
using std::endl;

// --- Допоміжна функція для поліморфного завантаження ---

/**
 * @brief Динамічно створює об'єкт Document на основі його типу (перший токен у рядку).
 * @param line - Повний рядок із файлу.
 * @return Унікальний вказівник на створений об'єкт-нащадок.
 */
std::unique_ptr<Document> LibraryManager::CreateDocumentFromCsv(const std::string& line)
{
    // 1. Знаходимо тип документа
    size_t firstDelimiter = line.find(';');
    if (firstDelimiter == string::npos) return nullptr;

    string docType = line.substr(0, firstDelimiter);
    string docData = line.substr(firstDelimiter + 1); // Решта даних для FromCsv

    std::unique_ptr<Document> doc = nullptr;

    // 2. Створюємо відповідний клас
    if (docType == "Printed")
    {
        doc = std::make_unique<PrintedDocument>();
    }
    else if (docType == "Electronic")
    {
        doc = std::make_unique<ElectronicDocument>();
    }

    // 3. Заповнюємо дані
    if (doc)
    {
        doc->FromCsv(docData);
    }

    return doc;
}

// --- Конструктор / Деструктор ---

LibraryManager::LibraryManager() : currentUser(nullptr)
{
    // Завантажуємо всі дані при запуску програми
    LoadAllData();
    // Створюємо базового адміністратора, якщо список користувачів порожній
    if (users.empty()) {
        RegisterUser("admin", "admin123", true);
    }
}

LibraryManager::~LibraryManager()
{
    // Зберігаємо всі дані при завершенні роботи
    SaveAllData();
}



// СЕКЦІЯ: РОБОТА З ФАЙЛАМИ


void LibraryManager::LoadAllData()
{
    // * Примітка: Для реалізації LoadAllData() потрібна допоміжна функція SplitCsvLine,
    // * яка була додана вище в анонімний простір імен.

    // 1. Завантаження Студентів
    std::ifstream studentFile(STUDENTS_FILE);
    string line;
    while (std::getline(studentFile, line)) {
        Student s;
        s.FromCsv(line);
        students.push_back(s);
    }

    // 2. Завантаження Документів (Поліморфне завантаження)
    std::ifstream docFile(DOCUMENTS_FILE);
    while (std::getline(docFile, line)) {
        // Ми очікуємо рядок у форматі: Type;ID;Title;Author...
        std::unique_ptr<Document> doc = CreateDocumentFromCsv(line);
        if (doc) {
            documents.push_back(std::move(doc));
        }
    }

    // 3. Завантаження Користувачів
    std::ifstream userFile(USERS_FILE);
    while (std::getline(userFile, line)) {
        User u;
        u.FromCsv(line);
        users.push_back(u);
    }

    // 4. Завантаження Транзакцій
    std::ifstream transFile(TRANSACTIONS_FILE);
    while (std::getline(transFile, line)) {
        BookRecord record;
        record.FromCsv(line);
        transactions.push_back(record);
    }

    cout << "Data loaded successfully." << endl;
}

void LibraryManager::SaveAllData() const
{
    // 1. Збереження Студентів
    std::ofstream studentFile(STUDENTS_FILE);
    for (const auto& s : students) {
        studentFile << s.ToCsv() << "\n";
    }

    // 2. Збереження Документів (Поліморфне збереження)
    std::ofstream docFile(DOCUMENTS_FILE);
    for (const auto& docPtr : documents) {
        // Записуємо тип, потім викликаємо ToCsv() поліморфно
        docFile << docPtr->GetType() << ";" << docPtr->ToCsv() << "\n";
    }

    // 3. Збереження Користувачів
    std::ofstream userFile(USERS_FILE);
    for (const auto& u : users) {
        userFile << u.ToCsv() << "\n";
    }

    // 4. Збереження Транзакцій
    std::ofstream transFile(TRANSACTIONS_FILE);
    for (const auto& r : transactions) {
        transFile << r.ToCsv() << "\n";
    }

    cout << "Data saved successfully." << endl;
}


// СЕКЦІЯ: АВТОРИЗАЦІЯ


bool LibraryManager::Login(const string& username, const string& password)
{
    // Шукаємо користувача за логіном
    auto it = std::find_if(users.begin(), users.end(),
        [&](const User& u) { return u.GetUsername() == username; });

    if (it != users.end() && it->GetPassword() == password) {
        // Знайшли і пароль співпадає
        currentUser = &(*it);
        cout << "Login successful. " << (currentUser->IsAdmin() ? "(Admin mode)" : "(User mode)") << endl;
        return true;
    }

    cout << "Login failed. Invalid username or password." << endl;
    return false;
}

void LibraryManager::Logout()
{
    currentUser = nullptr;
    cout << "Logout successful." << endl;
}

User* LibraryManager::GetCurrentUser() const
{
    return currentUser;
}

bool LibraryManager::RegisterUser(const string& username, const string& password, bool isAdmin)
{
    // Перевірка, чи вже існує користувач
    auto it = std::find_if(users.begin(), users.end(),
        [&](const User& u) { return u.GetUsername() == username; });

    if (it != users.end()) {
        cout << "Registration failed: User with this username already exists." << endl;
        return false;
    }

    users.emplace_back(username, password, isAdmin);
    SaveAllData(); // Зберігаємо негайно
    cout << "User '" << username << "' registered successfully." << endl;
    return true;
}

bool LibraryManager::DeleteUser(const string& username)
{
    // Тільки адміністратор може видаляти користувачів
    if (!currentUser || !currentUser->IsAdmin()) {
        cout << "Error: Only administrators can delete users." << endl;
        return false;
    }

    auto it = std::remove_if(users.begin(), users.end(),
        [&](const User& u) { return u.GetUsername() == username; });

    if (it != users.end()) {
        users.erase(it, users.end());
        SaveAllData();
        cout << "User '" << username << "' deleted successfully." << endl;
        return true;
    }

    cout << "Error: User '" << username << "' not found." << endl;
    return false;
}

void LibraryManager::DisplayUserList() const
{
    // Тільки адміністратор може бачити цей список
    if (!currentUser || !currentUser->IsAdmin()) {
        cout << "Error: Access denied. Only administrators can view user list." << endl;
        return;
    }
    cout << "--- User List ---" << endl;
    for (const auto& u : users) {
        cout << u.GetUsername() << " (" << (u.IsAdmin() ? "Admin" : "User") << ")" << endl;
    }
    cout << "-----------------" << endl;
}


// СЕКЦІЯ: CRUD ДЛЯ ДОКУМЕНТІВ (Приклад)

void LibraryManager::AddDocument(std::unique_ptr<Document> doc)
{
    // Генеруємо унікальний ID (проста інкрементація або пошук max ID)
    int maxId = 0;
    for (const auto& d : documents) {
        if (d->GetId() > maxId) maxId = d->GetId();
    }
    doc->SetId(maxId + 1);

    documents.push_back(std::move(doc));
    SaveAllData();
    cout << "Document added with ID: " << maxId + 1 << endl;
}

void LibraryManager::DisplayDocuments() const
{
    cout << "--- Library Documents (" << documents.size() << ") ---" << endl;
    for (const auto& docPtr : documents) {
        docPtr->DisplayInfo(); // Поліморфний виклик
    }
    cout << "-----------------------------------" << endl;
}


// СЕКЦІЯ: УПРАВЛІННЯ СТУДЕНТАМИ


void LibraryManager::AddStudent(const Student& student)
{
    // 1. Перевірка на дублікат картки читача
    auto it = std::find_if(students.begin(), students.end(),
        [&](const Student& s) { return s.GetReaderCardId() == student.GetReaderCardId(); });

    if (it != students.end()) {
        cout << "Error: Student with card ID " << student.GetReaderCardId() << " already exists." << endl;
        return;
    }

    // 2. Додавання
    students.push_back(student);
    SaveAllData(); // Автозбереження
    cout << "Student added successfully." << endl;
}

void LibraryManager::EditStudent(const std::string& cardId, const Student& updatedStudent)
{
    auto it = std::find_if(students.begin(), students.end(),
        [&](const Student& s) { return s.GetReaderCardId() == cardId; });

    if (it != students.end()) {
        *it = updatedStudent; // Оновлюємо дані (оператор присвоєння)
        SaveAllData();
        cout << "Student details updated." << endl;
    }
    else {
        cout << "Error: Student not found." << endl;
    }
}

bool LibraryManager::DeleteStudent(const std::string& cardId)
{
    // ! Важлива перевірка: Чи має студент неповернуті книги?
    auto transactionIt = std::find_if(transactions.begin(), transactions.end(),
        [&](const BookRecord& r) { return r.readerCardId == cardId; });

    if (transactionIt != transactions.end()) {
        cout << "Error: Cannot delete student. They have unreturned books!" << endl;
        return false;
    }

    auto it = std::remove_if(students.begin(), students.end(),
        [&](const Student& s) { return s.GetReaderCardId() == cardId; });

    if (it != students.end()) {
        students.erase(it, students.end());
        SaveAllData();
        cout << "Student deleted." << endl;
        return true;
    }

    cout << "Error: Student not found." << endl;
    return false;
}

void LibraryManager::DisplayStudents() const
{
    cout << "--- Registered Students (" << students.size() << ") ---" << endl;
    for (const auto& s : students) {
        s.DisplayInfo();
    }
    cout << "---------------------------------" << endl;
}


// СЕКЦІЯ: УПРАВЛІННЯ ДОКУМЕНТАМИ (Продовження)


bool LibraryManager::DeleteDocument(int id)
{
    // ! Перевірка: Чи видана ця книга комусь зараз?
    auto transIt = std::find_if(transactions.begin(), transactions.end(),
        [&](const BookRecord& r) { return r.documentId == id; });

    if (transIt != transactions.end()) {
        cout << "Error: Cannot delete document. It is currently checked out." << endl;
        return false;
    }

    // Використовуємо remove_if для unique_ptr
    auto it = std::remove_if(documents.begin(), documents.end(),
        [&](const std::unique_ptr<Document>& doc) { return doc->GetId() == id; });

    if (it != documents.end()) {
        documents.erase(it, documents.end());
        SaveAllData();
        cout << "Document deleted." << endl;
        return true;
    }

    cout << "Error: Document ID not found." << endl;
    return false;
}

void LibraryManager::EditDocument(int id, const Document& updatedData)
{
    // Знаходимо документ
    auto it = std::find_if(documents.begin(), documents.end(),
        [&](const std::unique_ptr<Document>& doc) { return doc->GetId() == id; });

    if (it != documents.end()) {
        // Оновлюємо спільні поля
        (*it)->SetTitle(updatedData.GetTitle());
        (*it)->SetAuthor(updatedData.GetAuthor());
        (*it)->SetYear(updatedData.GetYear());

        SaveAllData();
        cout << "Document basic info updated." << endl;
    }
    else {
        cout << "Error: Document not found." << endl;
    }
}


// СЕКЦІЯ: ОСНОВНА БІЗНЕС-ЛОГІКА (Check-in / Check-out)


bool LibraryManager::CheckoutBook(const std::string& cardId, int documentId)
{
    // 1. Перевіряємо, чи існує студент
    auto studentIt = std::find_if(students.begin(), students.end(),
        [&](const Student& s) { return s.GetReaderCardId() == cardId; });

    if (studentIt == students.end()) {
        cout << "Error: Student not found." << endl;
        return false;
    }

    // 2. Перевіряємо, чи існує документ
    auto docIt = std::find_if(documents.begin(), documents.end(),
        [&](const std::unique_ptr<Document>& d) { return d->GetId() == documentId; });

    if (docIt == documents.end()) {
        cout << "Error: Document not found." << endl;
        return false;
    }

    // 3. Перевіряємо, чи книга вже не видана (шукаємо в транзакціях)
    auto transIt = std::find_if(transactions.begin(), transactions.end(),
        [&](const BookRecord& r) { return r.documentId == documentId; });

    if (transIt != transactions.end()) {
        cout << "Error: Document is already checked out by someone else." << endl;
        return false;
    }

    // 4. Створюємо запис про видачу
    BookRecord record;
    record.documentId = documentId;
    record.readerCardId = cardId;

    // Час видачі = зараз
    record.issueDate = std::time(nullptr);

    // Час повернення = зараз + 14 днів (14 * 24 * 60 * 60 секунд)
    record.dueDate = record.issueDate + (14 * 24 * 60 * 60);

    transactions.push_back(record);
    SaveAllData();

    cout << "Success: '" << (*docIt)->GetTitle() << "' checked out to "
        << studentIt->GetFullName() << "." << endl;
    return true;
}

bool LibraryManager::ReturnBook(const std::string& cardId, int documentId)
{
    // Шукаємо запис, де співпадає і ID книги, і ID студента
    auto it = std::remove_if(transactions.begin(), transactions.end(),
        [&](const BookRecord& r) {
            return r.documentId == documentId && r.readerCardId == cardId;
        });

    if (it != transactions.end()) {
        transactions.erase(it, transactions.end());
        SaveAllData();
        cout << "Success: Book returned." << endl;
        return true;
    }

    cout << "Error: No such transaction found (Student didn't take this book)." << endl;
    return false;
}

void LibraryManager::DisplayDebtorList() const
{
    std::time_t now = std::time(nullptr);
    bool found = false;

    cout << "--- List of Debtors (Overdue Books) ---" << endl;

    for (const auto& r : transactions) {
        // Якщо поточний час більше за дедлайн (dueDate)
        if (now > r.dueDate) {
            found = true;

            // Шукаємо деталі для гарного виводу
            string studentName = "Unknown";
            string bookTitle = "Unknown";

            auto sIt = std::find_if(students.begin(), students.end(),
                [&](const Student& s) { return s.GetReaderCardId() == r.readerCardId; });
            if (sIt != students.end()) studentName = sIt->GetFullName();

            auto dIt = std::find_if(documents.begin(), documents.end(),
                [&](const std::unique_ptr<Document>& d) { return d->GetId() == r.documentId; });
            if (dIt != documents.end()) bookTitle = (*dIt)->GetTitle();

            cout << "DEBTOR: " << studentName << " | Book: " << bookTitle
                << " | Overdue since: " << std::ctime(&r.dueDate); // ctime перетворює час у рядок
        }
    }

    if (!found) cout << "No debtors found." << endl;
    cout << "---------------------------------------" << endl;
}


// СЕКЦІЯ: ПОШУК ТА СОРТУВАННЯ


std::vector<Document*> LibraryManager::SearchDocuments(const std::string& query) const
{
    std::vector<Document*> results;
    string q = query;
    // Тут можна було б перевести q в нижній регістр для нечутливості до регістру

    for (const auto& doc : documents) {
        // Шукаємо підстроку в назві або авторі
        if (doc->GetTitle().find(q) != string::npos ||
            doc->GetAuthor().find(q) != string::npos) {
            results.push_back(doc.get()); // .get() повертає сирий вказівник з unique_ptr
        }
    }
    return results;
}

void LibraryManager::SortDocumentsByTitle()
{
    // Використовуємо лямбда-вираз для порівняння
    std::sort(documents.begin(), documents.end(),
        [](const std::unique_ptr<Document>& a, const std::unique_ptr<Document>& b) {
            return a->GetTitle() < b->GetTitle();
        });

    cout << "Documents sorted by title." << endl;
    DisplayDocuments();
}

std::vector<Document*> LibraryManager::FilterDocumentsByType(const std::string& type) const
{
    std::vector<Document*> results;
    for (const auto& doc : documents) {
        if (doc->GetType() == type) {
            results.push_back(doc.get());
        }
    }
    return results;
}

