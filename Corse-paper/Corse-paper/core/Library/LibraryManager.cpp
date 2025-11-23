#define _CRT_SECURE_NO_WARNINGS // Вимикає помилку про "небезпечний" ctime
#include "LibraryManager.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <ctime>     
#include <iomanip>

// Константи імен файлів
namespace
{
    const std::string STUDENTS_FILE = "students.txt";
    const std::string DOCUMENTS_FILE = "documents.txt";
    const std::string USERS_FILE = "users.txt";
    const std::string TRANSACTIONS_FILE = "transactions.txt";
}

using namespace LibraryCore;
using std::string;
using std::cout;
using std::endl;

// Допоміжні методи

// Метод: визначає тип документа за першим словом у рядку CSV
std::unique_ptr<Document> LibraryManager::CreateDocumentFromCsv(const std::string& line)
{
    size_t firstDelimiter = line.find(';');
    if (firstDelimiter == string::npos) return nullptr;

    string docType = line.substr(0, firstDelimiter);
    string docData = line.substr(firstDelimiter + 1);

    std::unique_ptr<Document> doc = nullptr;

    if (docType == "Printed") {
        doc = std::make_unique<PrintedDocument>();
    }
    else if (docType == "Electronic") {
        doc = std::make_unique<ElectronicDocument>();
    }

    if (doc) {
        doc->FromCsv(docData);
    }
    return doc;
}

// Конструктор та деструктор

LibraryManager::LibraryManager() : currentUser(nullptr)
{
    LoadAllData();

    if (users.empty()) {
        RegisterUser("admin", "admin123", true);
    }
}

LibraryManager::~LibraryManager()
{
    SaveAllData();
}

// Авторизація

bool LibraryManager::Login(const string& username, const string& password)
{
    auto it = std::find_if(users.begin(), users.end(),
        [&](const User& u) { return u.GetUsername() == username; });

    if (it != users.end() && it->GetPassword() == password) {
        currentUser = &(*it);
        return true;
    }
    return false;
}

void LibraryManager::Logout()
{
    currentUser = nullptr;
}

User* LibraryManager::GetCurrentUser() const
{
    return currentUser;
}

// Адміністративні функції

bool LibraryManager::RegisterUser(const string& username, const string& password, bool isAdmin)
{
    auto it = std::find_if(users.begin(), users.end(),
        [&](const User& u) { return u.GetUsername() == username; });

    if (it != users.end()) {
        cout << "Помилка: Користувач з таким логіном вже існує!" << endl;
        return false;
    }

    users.emplace_back(username, password, isAdmin);
    SaveAllData();
    cout << "Успіх: Користувача зареєстровано." << endl;
    return true;
}

bool LibraryManager::DeleteUser(const string& username)
{
    if (!currentUser || !currentUser->IsAdmin()) return false;

    if (currentUser->GetUsername() == username) {
        cout << "Помилка: Неможливо видалити власний акаунт." << endl;
        return false;
    }

    auto it = std::remove_if(users.begin(), users.end(),
        [&](const User& u) { return u.GetUsername() == username; });

    if (it != users.end()) {
        users.erase(it, users.end());
        SaveAllData();
        cout << "Успіх: Користувача видалено." << endl;
        return true;
    }
    cout << "Помилка: Користувача не знайдено." << endl;
    return false;
}

void LibraryManager::DisplayUserList() const
{
    if (!currentUser || !currentUser->IsAdmin()) return;
    cout << "--- Список користувачів системи ---" << endl;
    for (const auto& u : users) {
        cout << " - " << u.GetUsername() << " (" << (u.IsAdmin() ? "Адміністратор" : "Користувач") << ")" << endl;
    }
    cout << "-----------------------------------" << endl;
}

// Робота з файлами

void LibraryManager::LoadAllData()
{
    // 1. Завантаження студентів
    std::ifstream studentFile(STUDENTS_FILE);
    string line;
    while (std::getline(studentFile, line)) {
        Student s; s.FromCsv(line);
        students.push_back(s);
    }

    // 2. Завантаження документів
    std::ifstream docFile(DOCUMENTS_FILE);
    while (std::getline(docFile, line)) {
        auto doc = CreateDocumentFromCsv(line);
        if (doc) documents.push_back(std::move(doc));
    }

    // 3. Завантаження користувачів
    std::ifstream userFile(USERS_FILE);
    while (std::getline(userFile, line)) {
        User u; u.FromCsv(line);
        users.push_back(u);
    }

    // 4. Завантаження історії видач
    std::ifstream transFile(TRANSACTIONS_FILE);
    while (std::getline(transFile, line)) {
        BookRecord record; record.FromCsv(line);
        transactions.push_back(record);
    }
}

void LibraryManager::SaveAllData() const
{
    // 1. Збереження студентів
    std::ofstream studentFile(STUDENTS_FILE);
    for (const auto& s : students) studentFile << s.ToCsv() << "\n";

    // 2. Збереження документів
    std::ofstream docFile(DOCUMENTS_FILE);
    for (const auto& docPtr : documents) {
        docFile << docPtr->GetType() << ";" << docPtr->ToCsv() << "\n";
    }

    // 3. Збереження користувачів
    std::ofstream userFile(USERS_FILE);
    for (const auto& u : users) userFile << u.ToCsv() << "\n";

    // 4. Збереження транзакцій
    std::ofstream transFile(TRANSACTIONS_FILE);
    for (const auto& r : transactions) transFile << r.ToCsv() << "\n";
}

// Управління студентами

void LibraryManager::AddStudent(const Student& student)
{

    auto it = std::find_if(students.begin(), students.end(),
        [&](const Student& s) { return s.GetReaderCardId() == student.GetReaderCardId(); });

    if (it != students.end()) {
        cout << "Помилка: Студент з таким читацьким квитком вже існує." << endl;
        return;
    }
    students.push_back(student);
    SaveAllData();
    cout << "Успіх: Студента додано." << endl;
}

void LibraryManager::EditStudent(const std::string& cardId, const Student& updatedStudent)
{
    auto it = std::find_if(students.begin(), students.end(),
        [&](const Student& s) { return s.GetReaderCardId() == cardId; });

    if (it != students.end()) {
        *it = updatedStudent;
        SaveAllData();
        cout << "Успіх: Дані студента оновлено." << endl;
    }
    else {
        cout << "Помилка: Студента не знайдено." << endl;
    }
}

bool LibraryManager::DeleteStudent(const std::string& cardId)
{
    auto transactionIt = std::find_if(transactions.begin(), transactions.end(),
        [&](const BookRecord& r) { return r.readerCardId == cardId; });

    if (transactionIt != transactions.end()) {
        cout << "Помилка: Неможливо видалити. Студент має неповернуті книги!" << endl;
        return false;
    }

    auto it = std::remove_if(students.begin(), students.end(),
        [&](const Student& s) { return s.GetReaderCardId() == cardId; });

    if (it != students.end()) {
        students.erase(it, students.end());
        SaveAllData();
        cout << "Успіх: Студента видалено." << endl;
        return true;
    }
    cout << "Помилка: Студента не знайдено." << endl;
    return false;
}

void LibraryManager::DisplayStudents() const
{
    if (students.empty()) { cout << "Список пустий." << endl; return; }

    string line = "+------------+-----------------+-----------------+-----------------+--------+------------+";

    cout << line << endl;
    cout << "| " << std::left << std::setw(10) << "ID Картки"
        << " | " << std::setw(15) << "Прізвище"
        << " | " << std::setw(15) << "Ім'я"
        << " | " << std::setw(15) << "Залікова"
        << " | " << std::setw(6) << "Курс"
        << " | " << std::setw(10) << "Група" << " |" << endl;
    cout << line << endl;

    for (const auto& s : students) {
        cout << "| " << std::left << std::setw(10) << s.GetReaderCardId()
            << " | " << std::setw(15) << s.GetLastName()
            << " | " << std::setw(15) << s.GetFirstName()
            << " | " << std::setw(15) << s.GetRecordBookNumber()
            << " | " << std::setw(6) << s.GetCourse()
            << " | " << std::setw(10) << s.GetGroup() << " |" << endl;
    }
    cout << line << endl;
    cout << " Всього: " << students.size() << endl;
}

// Управління документами


void LibraryManager::AddDocument(std::unique_ptr<Document> doc)
{
    int maxId = 0;
    for (const auto& d : documents) {
        if (d->GetId() > maxId) maxId = d->GetId();
    }
    doc->SetId(maxId + 1);

    documents.push_back(std::move(doc));
    SaveAllData();
    cout << "Успіх: Документ додано (ID: " << maxId + 1 << ")" << endl;
}

void LibraryManager::EditDocument(int id, const Document& updatedData)
{
    auto it = std::find_if(documents.begin(), documents.end(),
        [&](const std::unique_ptr<Document>& doc) { return doc->GetId() == id; });

    if (it != documents.end()) {
        (*it)->SetTitle(updatedData.GetTitle());
        (*it)->SetAuthor(updatedData.GetAuthor());
        (*it)->SetYear(updatedData.GetYear());
        SaveAllData();
        cout << "Успіх: Базові дані документа оновлено." << endl;
    }
    else {
        cout << "Помилка: Документ не знайдено." << endl;
    }
}

bool LibraryManager::DeleteDocument(int id)
{
    auto transIt = std::find_if(transactions.begin(), transactions.end(),
        [&](const BookRecord& r) { return r.documentId == id; });

    if (transIt != transactions.end()) {
        cout << "Помилка: Неможливо видалити. Документ зараз у читача." << endl;
        return false;
    }

    auto it = std::remove_if(documents.begin(), documents.end(),
        [&](const std::unique_ptr<Document>& doc) { return doc->GetId() == id; });

    if (it != documents.end()) {
        documents.erase(it, documents.end());
        SaveAllData();
        cout << "Успіх: Документ видалено." << endl;
        return true;
    }
    cout << "Помилка: Документ з таким ID не знайдено." << endl;
    return false;
}

void LibraryManager::DisplayDocuments() const
{
    if (documents.empty()) { cout << "Фонд пустий." << endl; return; }

    string line = "+------+------------+-------------------------+--------------------+--------+-------------------------------------+";

    cout << line << endl;
    cout << "| " << std::left << std::setw(4) << "ID"
        << " | " << std::setw(10) << "Тип"
        << " | " << std::setw(23) << "Назва"
        << " | " << std::setw(18) << "Автор"
        << " | " << std::setw(6) << "Рік"
        << " | " << std::setw(35) << "Деталі" << " |" << endl;
    cout << line << endl;

    for (const auto& docPtr : documents) {
        string title = docPtr->GetTitle();
        if (title.length() > 23) title = title.substr(0, 20) + "...";

        string author = docPtr->GetAuthor();
        if (author.length() > 18) author = author.substr(0, 15) + "...";

        cout << "| " << std::left << std::setw(4) << docPtr->GetId()
            << " | " << std::setw(10) << docPtr->GetType()
            << " | " << std::setw(23) << title
            << " | " << std::setw(18) << author
            << " | " << std::setw(6) << docPtr->GetYear()
            << " | " << std::setw(35) << docPtr->GetDetails() << " |" << endl;
    }
    cout << line << endl;
    cout << " Всього: " << documents.size() << endl;
}

//Логіка видачі та повернення книг


bool LibraryManager::CheckoutBook(const string& cardId, int documentId)
{
    // 1. Чи існує студент?
    auto sIt = std::find_if(students.begin(), students.end(),
        [&](const Student& s) { return s.GetReaderCardId() == cardId; });
    if (sIt == students.end()) {
        cout << "Помилка: Студента не знайдено." << endl; return false;
    }

    // 2. Чи існує документ?
    auto dIt = std::find_if(documents.begin(), documents.end(),
        [&](const std::unique_ptr<Document>& d) { return d->GetId() == documentId; });
    if (dIt == documents.end()) {
        cout << "Помилка: Документ не знайдено." << endl; return false;
    }

    // 3. Чи документ вільний?
    auto tIt = std::find_if(transactions.begin(), transactions.end(),
        [&](const BookRecord& r) { return r.documentId == documentId; });
    if (tIt != transactions.end()) {
        cout << "Помилка: Цей документ вже виданий." << endl; return false;
    }

    // Видача
    BookRecord record;
    record.documentId = documentId;
    record.readerCardId = cardId;
    record.issueDate = std::time(nullptr);          
    record.dueDate = record.issueDate + (14 * 24 * 60 * 60); 

    transactions.push_back(record);
    SaveAllData();
    cout << "Успіх: Книгу видано." << endl;
    return true;
}

bool LibraryManager::ReturnBook(const string& cardId, int documentId)
{
    auto it = std::remove_if(transactions.begin(), transactions.end(),
        [&](const BookRecord& r) {
            return r.documentId == documentId && r.readerCardId == cardId;
        });

    if (it != transactions.end()) {
        transactions.erase(it, transactions.end());
        SaveAllData();
        cout << "Успіх: Книгу повернуто." << endl;
        return true;
    }
    cout << "Помилка: Запис про видачу не знайдено (Студент не брав цю книгу)." << endl;
    return false;
}

void LibraryManager::DisplayDebtorList() const
{
    std::time_t now = std::time(nullptr);
    bool found = false;
    cout << "--- Список боржників (Прострочені книги) ---" << endl;

    for (const auto& r : transactions) {
        if (now > r.dueDate) {
            found = true;
            cout << "Студент ID: " << r.readerCardId
                << " | Книга ID: " << r.documentId << " (ПРОСТРОЧЕНО)" << endl;
        }
    }

    if (!found) cout << "Боржників немає." << endl;
    cout << "--------------------------------------------" << endl;
}

// Пошук, сортування, фільтрація

std::vector<Document*> LibraryManager::SearchDocuments(const string& query) const
{
    std::vector<Document*> results;
    for (const auto& doc : documents) {
        if (doc->GetTitle().find(query) != string::npos ||
            doc->GetAuthor().find(query) != string::npos) {
            results.push_back(doc.get());
        }
    }
    return results;
}

void LibraryManager::SortDocumentsByTitle()
{
    std::sort(documents.begin(), documents.end(),
        [](const std::unique_ptr<Document>& a, const std::unique_ptr<Document>& b) {
            return a->GetTitle() < b->GetTitle();
        });
    cout << "Виконано: Список документів відсортовано за назвою." << endl;
    DisplayDocuments();
}

std::vector<Document*> LibraryManager::FilterDocumentsByType(const string& type) const
{
    std::vector<Document*> results;
    for (const auto& doc : documents) {
        if (doc->GetType() == type) {
            results.push_back(doc.get());
        }
    }
    return results;
}