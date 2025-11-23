#include <iostream>
#include <string>
#include <limits>
#define NOMINMAX
#include <windows.h> 


#include "core/Library/LibraryManager.h"
#include "core/Document/PrintedDocument.h"
#include "core/Document/ElectronicDocument.h"

using namespace std;
using namespace LibraryCore;

// Визначення кольорів для консолі
enum ConsoleColor {
    BLACK = 0, BLUE = 1, GREEN = 2, CYAN = 3, RED = 4,
    MAGENTA = 5, BROWN = 6, LIGHTGRAY = 7, DARKGRAY = 8,
    LIGHTBLUE = 9, LIGHTGREEN = 10, LIGHTCYAN = 11,
    LIGHTRED = 12, LIGHTMAGENTA = 13, YELLOW = 14, WHITE = 15
};

void EnableAnsiSupport() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

// Функція для зміни кольору тексту
void SetColor(int text, int bg = 0) {
    string colorCode;
    switch (text) {
	case 0: colorCode = "30"; break; // Чорний
	case 1: colorCode = "34"; break; // Синій
	case 2: colorCode = "32"; break; // Зелений
	case 3: colorCode = "36"; break; // Голубий
	case 4: colorCode = "31"; break; // Червоний
	case 5: colorCode = "35"; break; // Магента
	case 6: colorCode = "33"; break; // Коричневий/жовтий
	case 7: colorCode = "37"; break; // Світло-сірий
	case 8: colorCode = "90"; break; // Темно-сірий
	case 9: colorCode = "94"; break; // Світло-синій
	case 10: colorCode = "92"; break; // Світло-зелений
	case 11: colorCode = "96"; break; // Світло-голубий
	case 12: colorCode = "91"; break; // Світло-червоний
	case 13: colorCode = "95"; break; // Світло-магента
	case 14: colorCode = "93"; break; // Жовтий
	case 15: colorCode = "97"; break; // Білий
    default: colorCode = "37"; break;
    }
    cout << "\033[" << colorCode << "m";
}

void ClearInput() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Перевірка на скасування операції
bool IsCancel(const string& val) {
    if (val == "0") {
        SetColor(YELLOW);
        cout << " >>> Операцію скасовано." << endl;
        SetColor(WHITE);
        return true;
    }
    return false;
}

// 2. Для цілих чисел (int)
bool IsCancel(int val) {
    if (val == 0) {
        SetColor(YELLOW);
        cout << " >>> Операцію скасовано." << endl;
        SetColor(WHITE);
        return true;
    }
    return false;
}

// 3. Для дробів (double)
bool IsCancel(double val) {
    if (val == 0.0) {
        SetColor(YELLOW);
        cout << " >>> Операцію скасовано." << endl;
        SetColor(WHITE);
        return true;
    }
    return false;
}

void ShowMenu(bool isAdmin) {
    SetColor(LIGHTCYAN);
    cout << "\n========================================" << endl;
    cout << "   СИСТЕМА УПРАВЛІННЯ БІБЛІОТЕКОЮ" << endl;
    cout << "========================================" << endl;
    SetColor(WHITE);

    SetColor(YELLOW); cout << "1."; SetColor(WHITE); cout << " Пошук документів (за назвою/автором)" << endl;
    SetColor(YELLOW); cout << "2."; SetColor(WHITE); cout << " Видати книгу студенту" << endl;
    SetColor(YELLOW); cout << "3."; SetColor(WHITE); cout << " Прийняти книгу від студента" << endl;
    SetColor(YELLOW); cout << "4."; SetColor(WHITE); cout << " Список боржників (прострочені книги)" << endl;

    SetColor(DARKGRAY); cout << "----------------------------------------" << endl;
    SetColor(YELLOW); cout << "5."; SetColor(WHITE); cout << " Додати нового студента" << endl;
    SetColor(YELLOW); cout << "6."; SetColor(WHITE); cout << " Додати новий документ" << endl;
    SetColor(YELLOW); cout << "7."; SetColor(WHITE); cout << " Видалити документ" << endl;

    SetColor(DARKGRAY); cout << "----------------------------------------" << endl;
    SetColor(YELLOW); cout << "8."; SetColor(WHITE); cout << " [РЕДАГУВАННЯ] Змінити дані студента" << endl;
    SetColor(YELLOW); cout << "9."; SetColor(WHITE); cout << " [РЕДАГУВАННЯ] Змінити дані документа" << endl;
    SetColor(YELLOW); cout << "10."; SetColor(WHITE); cout << " [СОРТУВАННЯ] Сортувати документи за назвою" << endl;
    SetColor(YELLOW); cout << "11."; SetColor(WHITE); cout << " [ФІЛЬТР] Показати тільки Книги або Файли" << endl;

    SetColor(DARKGRAY); cout << "----------------------------------------" << endl;
    SetColor(YELLOW); cout << "12."; SetColor(WHITE); cout << " Список усіх студентів" << endl;
    SetColor(YELLOW); cout << "13."; SetColor(WHITE); cout << " Список усіх документів" << endl;

    SetColor(LIGHTGREEN);
    cout << "14. Допомога (Інструкція)" << endl;
    SetColor(WHITE);

    if (isAdmin) {
        SetColor(LIGHTRED);
        cout << "----------------------------------------" << endl;
        cout << "--- ПАНЕЛЬ АДМІНІСТРАТОРА ---" << endl;
        SetColor(YELLOW); cout << "15."; SetColor(WHITE); cout << " Зареєструвати нового користувача" << endl;
        SetColor(YELLOW); cout << "16."; SetColor(WHITE); cout << " Видалити користувача" << endl;
        SetColor(YELLOW); cout << "17."; SetColor(WHITE); cout << " Список користувачів системи" << endl;
    }

    SetColor(DARKGRAY);
    cout << "----------------------------------------" << endl;
    SetColor(YELLOW); cout << "0."; SetColor(WHITE); cout << " Вихід" << endl;
    SetColor(LIGHTCYAN);
    cout << "========================================" << endl;
    SetColor(WHITE);
    cout << "Ваш вибір: ";
}

void ShowHelp() {
    system("cls");
    SetColor(LIGHTGREEN);
    cout << "\n============================================================" << endl;
    cout << "                    ІНСТРУКЦІЯ КОРИСТУВАЧА                    " << endl;
    cout << "============================================================" << endl;
    SetColor(WHITE);

    cout << "\n[1. ЗАГАЛЬНИЙ ОПИС]" << endl;
    cout << "Ця система призначена для автоматизації роботи бібліотекаря." << endl;
    cout << "Вона дозволяє вести облік студентів, книг (друкованих та електронних)" << endl;
    cout << "та контролювати процес видачі/повернення літератури." << endl;

    cout << "\n[2. ПРАВИЛА ВВОДУ ДАНИХ]" << endl;
    SetColor(YELLOW); cout << " - Текстові поля:"; SetColor(WHITE); cout << " Можна вводити з пробілами." << endl;
    SetColor(YELLOW); cout << " - ID:"; SetColor(WHITE); cout << " Мають бути унікальними. Рекомендовано англ. літери (S101)." << endl;
    SetColor(YELLOW); cout << " - Збереження:"; SetColor(WHITE); cout << " Автоматично при виході з програми." << endl;

    cout << "\n[3. ОПИС ОСНОВНИХ КОМАНД]" << endl;
    cout << " * Пошук: Знаходить документи за фрагментом назви або автора." << endl;
    cout << " * Видача/Повернення: Змінює статус книги та прив'язує її до студента." << endl;
    cout << " * Боржники: Показує список книг, які не повернули вчасно (14 днів)." << endl;

    cout << "\n[4. ВАЖЛИВО: ЯК СКАСУВАТИ ДІЮ]" << endl;
    SetColor(YELLOW); cout << " Введіть '0' (нуль)"; SetColor(WHITE);
    cout << " у будь-якому полі вводу, щоб перервати операцію" << endl;
    cout << " та повернутися до головного меню." << endl;

    if (true) {
        SetColor(LIGHTRED);
        cout << "\n[5. АДМІНІСТРАТОР]" << endl;
        cout << " Логін: admin | Пароль: admin123" << endl;
    }

    SetColor(LIGHTGREEN);
    cout << "============================================================" << endl;
    SetColor(WHITE);
}

int main() {
    // Налаштування української мови
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    EnableAnsiSupport();

    LibraryManager app;

    string username, password;
    bool loggedIn = false;

	// Авторизація користувача
    while (!loggedIn) {
        system("cls");

        SetColor(YELLOW);
        cout << "\n>>> ВХІД У СИСТЕМУ <<<" << endl;
        SetColor(DARKGRAY);
        cout << "(Default: admin / admin123)" << endl;
        SetColor(WHITE);

        cout << " Логін: "; cin >> username;
        cout << " Пароль: "; cin >> password;

        if (app.Login(username, password)) {
            loggedIn = true;
            SetColor(GREEN);
            cout << "\n Вхід успішний! Завантаження..." << endl;
            Sleep(1000);
        }
        else {
            SetColor(RED);
            cout << "\n Помилка входу. Невірний логін або пароль." << endl;
            SetColor(WHITE);
            cout << " Спробувати ще раз? (y/n): ";
            char choice; cin >> choice;
            if (choice == 'n' || choice == 'N') return 0;
        }
    }

	// Головне меню
    int choice;
    while (true) {
        bool isAdmin = false;
        if (app.GetCurrentUser()) {
            isAdmin = app.GetCurrentUser()->IsAdmin();
        }

        ShowMenu(isAdmin);

        if (!(cin >> choice)) {
            SetColor(RED);
            cout << " Некоректне введення. Введіть число." << endl;
            SetColor(WHITE);
            ClearInput();
            Sleep(1000);
            continue;
        }

        system("cls");
        cout << endl;

        switch (choice) {
        case 0:
            app.Logout();
            SetColor(GREEN);
            cout << " Робота завершена. Дані збережено." << endl;
            return 0;

        case 1: { // Пошук
            string query;
            cout << " Введіть назву або автора: ";
            cin.ignore(); getline(cin, query);
            if (IsCancel(query)) break;

            auto results = app.SearchDocuments(query);

            SetColor(CYAN);
            cout << "\n Знайдено документів: " << results.size() << endl;
            SetColor(WHITE);
            for (auto* doc : results) doc->DisplayInfo();
            break;
        }

        case 2: { // Видача
            string cardId; int docId;
            cout << " ID картки студента: "; cin >> cardId; 
            if (IsCancel(cardId)) break;
            cout << " ID документа: "; cin >> docId; 
            if (IsCancel(docId)) break;

            if (app.CheckoutBook(cardId, docId)) { SetColor(GREEN); cout << " Успіх!\n"; }
            else { SetColor(RED); cout << " Помилка!\n"; }
            break;
        }

        case 3: { // Повернення
            string cardId; int docId;
            cout << " ID картки студента: "; cin >> cardId; if (IsCancel(cardId)) break;
            cout << " ID документа: "; cin >> docId; if (IsCancel(docId)) break;

            if (app.ReturnBook(cardId, docId)) { SetColor(GREEN); cout << " Успіх!\n"; }
            else { SetColor(RED); cout << " Помилка!\n"; }
            break;
        }

        case 4: // Боржники
            app.DisplayDebtorList();
            break;

        case 5: { // Додавання студента
            string lName, fName, recBook, group, cardId;
            int course;
            cout << "Прізвище: "; cin >> lName; if (IsCancel(lName)) break;
            cout << "Ім'я: "; cin >> fName; if (IsCancel(fName)) break;
            cout << "Номер залікової: "; cin >> recBook; if (IsCancel(recBook)) break;
            cout << "Курс (1-6): "; cin >> course; if (IsCancel(course)) break;
            cout << "Група: "; cin >> group; if (IsCancel(group)) break;
            cout << "Номер чит. квитка: "; cin >> cardId; if (IsCancel(cardId)) break;

            Student s(lName, fName, recBook, course, group, cardId);
            app.AddStudent(s);
            break;
        }

        case 6: { // Додавання документа
            int typeChoice;
            cout << "Тип? (1 - Друкований, 2 - Електронний): ";
            cin >> typeChoice; if (IsCancel(typeChoice)) break;

            string title, author;
            int year;
            cout << "Назва: "; cin.ignore(); getline(cin, title); if (IsCancel(title)) break;
            cout << "Автор: "; getline(cin, author); if (IsCancel(author)) break;
            cout << "Рік: "; cin >> year; if (IsCancel(year)) break;

            if (typeChoice == 1) {
                int pages;
                string medium;
                cout << "Сторінок: "; cin >> pages; if (IsCancel(pages)) break;
                cout << "Палітурка: "; cin.ignore(); getline(cin, medium); if (IsCancel(medium)) break;
                app.AddDocument(make_unique<PrintedDocument>(0, title, author, year, pages, medium));
            }
            else if (typeChoice == 2) {
                string format;
                double size;
                cout << "Формат (PDF/EPUB): "; cin >> format; if (IsCancel(format)) break;
                cout << "Розмір (MB): "; cin >> size; if (IsCancel(size)) break;
                app.AddDocument(make_unique<ElectronicDocument>(0, title, author, year, format, size));
            }
            break;
        }

        case 7: { // Видалення документа
            int id;
            cout << "ID документа для видалення: "; cin >> id;
            if (IsCancel(id)) break;
            app.DeleteDocument(id);
            break;
        }

        case 8: { // Редагування студента
            string targetId;
            cout << "Введіть ID картки студента, якого редагуємо: "; cin >> targetId; if (IsCancel(targetId)) break;

            string lName, fName, recBook, group;
            int course;
            cout << "--- Введіть НОВІ дані ---" << endl;
            cout << "Прізвище: "; cin >> lName; if (IsCancel(lName)) break;
            cout << "Ім'я: "; cin >> fName;
            cout << "Залікова: "; cin >> recBook;
            cout << "Курс: "; cin >> course;
            cout << "Група: "; cin >> group;

            Student updatedS(lName, fName, recBook, course, group, targetId);

            app.EditStudent(targetId, updatedS);
            break;
        }

        case 9: { // Редагування документа
            int targetId;
            cout << "Введіть ID документа для зміни: "; cin >> targetId; if (IsCancel(targetId)) break;

            string title, author;
            int year;
            cout << "--- Введіть НОВІ дані ---" << endl;
            cout << "Назва: "; cin.ignore(); getline(cin, title); if (IsCancel(title)) break;
            cout << "Автор: "; getline(cin, author);
            cout << "Рік: "; cin >> year;       

            PrintedDocument tempDoc(targetId, title, author, year, 0, "");
            app.EditDocument(targetId, tempDoc);
            break;
        }

        case 10: { // Сортування
            app.SortDocumentsByTitle();
            break;
        }

        case 11: { // Фільтрація
            int fType;
            cout << "Показати: 1-Друковані, 2-Електронні: "; cin >> fType; if (IsCancel(fType)) break;
            string typeStr = (fType == 1) ? "Printed" : "Electronic";

            auto filtered = app.FilterDocumentsByType(typeStr);
            cout << "\n--- Результат фільтрації (" << typeStr << ") ---" << endl;
            for (auto* doc : filtered) doc->DisplayInfo();
            cout << "----------------------------------------" << endl;
            break;
        }
                
        case 12: // Список студентів
            app.DisplayStudents();
            break;

        case 13: // Список документів
            app.DisplayDocuments();
            break;

		case 14: // Допомога
            ShowHelp();
            break;

        case 15: {// Функції Адміністратора
            if (!isAdmin) { cout << "Доступ заборонено.\n"; break; }
            string uName, uPass;
            bool adminFlag;
            cout << "Новий логін: "; cin >> uName; if (IsCancel(uName)) break;
            cout << "Новий пароль: "; cin >> uPass; if (IsCancel(uPass)) break;
            cout << "Права адміна? (1-Так, 0-Ні): "; cin >> adminFlag;
            app.RegisterUser(uName, uPass, adminFlag);
            break;
        }

        case 16: {
            if (!isAdmin) { cout << "Доступ заборонено.\n"; break; }
            string uName;
            cout << "Логін для видалення: "; cin >> uName; if (IsCancel(uName)) break;
            app.DeleteUser(uName);
            break;
        }

        case 17: {
            if (!isAdmin) { cout << "Доступ заборонено.\n"; break; }
            app.DisplayUserList();
            break;
        }

        default:
            SetColor(RED);
            cout << " Невірний вибір." << endl;
        }

        SetColor(DARKGRAY);
        cout << "\n [Натисніть Enter для повернення в меню...]";
        SetColor(WHITE);
        cin.ignore(); cin.get();
    }

    return 0;
}