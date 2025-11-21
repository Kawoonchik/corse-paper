#include <iostream>
#include <string>
#include <limits> // Для очищення буфера вводу
#define NOMINMAX
#include <windows.h> // Для налаштування кодування (SetConsoleOutputCP)

// --- ПІДКЛЮЧЕННЯ ЯДРА ---
// Шляхи прописані на основі твоєї структури папок
#include "core/Library/LibraryManager.h"
#include "core/Document/PrintedDocument.h"
#include "core/Document/ElectronicDocument.h"

using namespace std;
using namespace LibraryCore;

// Функція для очищення потоку (якщо ввели букви замість цифр)
void ClearInput() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Функція відображення меню
void ShowMenu(bool isAdmin) {
    cout << "\n========================================" << endl;
    cout << "   СИСТЕМА УПРАВЛІННЯ БІБЛІОТЕКОЮ" << endl;
    cout << "========================================" << endl;
    cout << "1. Пошук документів (за назвою/автором)" << endl;
    cout << "2. Видати книгу студенту" << endl;
    cout << "3. Прийняти книгу від студента" << endl;
    cout << "4. Список боржників (прострочені книги)" << endl;
    cout << "----------------------------------------" << endl;
    cout << "5. Додати нового студента" << endl;
    cout << "6. Додати новий документ" << endl;
    cout << "7. Видалити документ" << endl;
    cout << "----------------------------------------" << endl;
    cout << "8. [РЕДАГУВАННЯ] Змінити дані студента" << endl;
    cout << "9. [РЕДАГУВАННЯ] Змінити дані документа" << endl;
    cout << "10. [СОРТУВАННЯ] Сортувати документи за назвою" << endl;
    cout << "11. [ФІЛЬТР] Показати тільки Книги або Файли" << endl;
    cout << "----------------------------------------" << endl;
    cout << "12. Список усіх студентів" << endl;
    cout << "13. Список усіх документів" << endl;

    if (isAdmin) {
        cout << "----------------------------------------" << endl;
        cout << "--- ПАНЕЛЬ АДМІНІСТРАТОРА ---" << endl;
        cout << "14. Зареєструвати нового користувача" << endl;
        cout << "15. Видалити користувача" << endl;
        cout << "16. Список користувачів системи" << endl;
    }

    cout << "----------------------------------------" << endl;
    cout << "0. Вихід" << endl;
    cout << "========================================" << endl;
    cout << "Ваш вибір: ";
}

int main() {
    // 1. Налаштування української мови
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // 2. Ініціалізація системи
    LibraryManager app;

    string username, password;
    bool loggedIn = false;

    // === ЕТАП 1: АВТОРИЗАЦІЯ ===
    while (!loggedIn) {
        cout << "\n--- ВХІД У СИСТЕМУ ---" << endl;
        cout << "(За замовчуванням: admin / admin123)" << endl;

        cout << "Логін: "; cin >> username;
        cout << "Пароль: "; cin >> password;

        if (app.Login(username, password)) {
            loggedIn = true;
        }
        else {
            cout << "Помилка входу. Спробувати ще раз? (y/n): ";
            char choice; cin >> choice;
            if (choice == 'n' || choice == 'N') return 0;
        }
    }

    // === ЕТАП 2: ГОЛОВНЕ МЕНЮ ===
    int choice;
    while (true) {
        bool isAdmin = false;
        if (app.GetCurrentUser()) {
            isAdmin = app.GetCurrentUser()->IsAdmin();
        }

        ShowMenu(isAdmin);

        if (!(cin >> choice)) {
            cout << "Некоректне введення. Введіть число." << endl;
            ClearInput();
            continue;
        }

        switch (choice) {
        case 0:
            app.Logout();
            return 0;

        case 1: { // Пошук
            string query;
            cout << "Введіть частину назви або автора: ";
            cin.ignore(); getline(cin, query);

            auto results = app.SearchDocuments(query);
            cout << "\nЗнайдено документів: " << results.size() << endl;
            for (auto* doc : results) doc->DisplayInfo();
            break;
        }
        case 2: { // Видача
            string cardId;
            int docId;
            cout << "ID картки студента: "; cin >> cardId;
            cout << "ID документа: "; cin >> docId;
            app.CheckoutBook(cardId, docId);
            break;
        }
        case 3: { // Повернення
            string cardId;
            int docId;
            cout << "ID картки студента: "; cin >> cardId;
            cout << "ID документа: "; cin >> docId;
            app.ReturnBook(cardId, docId);
            break;
        }
        case 4: // Боржники
            app.DisplayDebtorList();
            break;

        case 5: { // Додавання студента
            string lName, fName, recBook, group, cardId;
            int course;
            cout << "Прізвище: "; cin >> lName;
            cout << "Ім'я: "; cin >> fName;
            cout << "Номер залікової: "; cin >> recBook;
            cout << "Курс (1-6): "; cin >> course;
            cout << "Група: "; cin >> group;
            cout << "Номер чит. квитка (унікальний): "; cin >> cardId;

            Student s(lName, fName, recBook, course, group, cardId);
            app.AddStudent(s);
            break;
        }
        case 6: { // Додавання документа
            int typeChoice;
            cout << "Тип? (1 - Друкований, 2 - Електронний): ";
            cin >> typeChoice;

            string title, author;
            int year;
            cout << "Назва: "; cin.ignore(); getline(cin, title);
            cout << "Автор: "; getline(cin, author);
            cout << "Рік: "; cin >> year;

            if (typeChoice == 1) {
                int pages;
                string medium;
                cout << "Сторінок: "; cin >> pages;
                cout << "Палітурка: "; cin.ignore(); getline(cin, medium);
                app.AddDocument(make_unique<PrintedDocument>(0, title, author, year, pages, medium));
            }
            else if (typeChoice == 2) {
                string format;
                double size;
                cout << "Формат (PDF/EPUB): "; cin >> format;
                cout << "Розмір (MB): "; cin >> size;
                app.AddDocument(make_unique<ElectronicDocument>(0, title, author, year, format, size));
            }
            break;
        }
        case 7: { // Видалення документа
            int id;
            cout << "ID документа для видалення: "; cin >> id;
            app.DeleteDocument(id);
            break;
        }

        case 8: { // Редагування студента
            string targetId;
            cout << "Введіть ID картки студента, якого редагуємо: "; cin >> targetId;

            // Збираємо нові дані
            string lName, fName, recBook, group;
            int course;
            cout << "--- Введіть НОВІ дані ---" << endl;
            cout << "Прізвище: "; cin >> lName;
            cout << "Ім'я: "; cin >> fName;
            cout << "Залікова: "; cin >> recBook;
            cout << "Курс: "; cin >> course;
            cout << "Група: "; cin >> group;

            // Створюємо об'єкт з новими даними (ID залишаємо той самий, щоб не ламати зв'язки)
            Student updatedS(lName, fName, recBook, course, group, targetId);

            app.EditStudent(targetId, updatedS);
            break;
        }
        case 9: { // Редагування документа
            int targetId;
            cout << "Введіть ID документа для зміни: "; cin >> targetId;

            // Збираємо нові базові дані
            string title, author;
            int year;
            cout << "--- Введіть НОВІ дані ---" << endl;
            cout << "Назва: "; cin.ignore(); getline(cin, title);
            cout << "Автор: "; getline(cin, author);
            cout << "Рік: "; cin >> year;

            // Створюємо тимчасовий об'єкт, щоб передати дані (тип тут не важливий, бо ми міняємо тільки спільні поля)
            PrintedDocument tempDoc(targetId, title, author, year, 0, "");
            app.EditDocument(targetId, tempDoc);
            break;
        }
        case 10: { // Сортування
            app.SortDocumentsByTitle(); // Метод вже має cout всередині
            break;
        }
        case 11: { // Фільтрація
            int fType;
            cout << "Показати: 1-Друковані, 2-Електронні: "; cin >> fType;
            string typeStr = (fType == 1) ? "Printed" : "Electronic";

            auto filtered = app.FilterDocumentsByType(typeStr);
            cout << "\n--- Результат фільтрації (" << typeStr << ") ---" << endl;
            for (auto* doc : filtered) doc->DisplayInfo();
            cout << "----------------------------------------" << endl;
            break;
        }

               // --------------------

        case 12: // Список студентів
            app.DisplayStudents();
            break;
        case 13: // Список документів
            app.DisplayDocuments();
            break;

            // --- Функції Адміністратора ---
        case 14: {
            if (!isAdmin) { cout << "Доступ заборонено.\n"; break; }
            string uName, uPass;
            bool adminFlag;
            cout << "Новий логін: "; cin >> uName;
            cout << "Новий пароль: "; cin >> uPass;
            cout << "Права адміна? (1-Так, 0-Ні): "; cin >> adminFlag;
            app.RegisterUser(uName, uPass, adminFlag);
            break;
        }
        case 15: {
            if (!isAdmin) { cout << "Доступ заборонено.\n"; break; }
            string uName;
            cout << "Логін для видалення: "; cin >> uName;
            app.DeleteUser(uName);
            break;
        }
        case 16: {
            if (!isAdmin) { cout << "Доступ заборонено.\n"; break; }
            app.DisplayUserList();
            break;
        }

        default:
            cout << "Невірний вибір." << endl;
        }

        cout << "\n[Enter] -> Меню";
        cin.ignore(); cin.get();
    }

    return 0;
}