#include <iostream>
#include <string>
#include <limits>
#define NOMINMAX
#include <windows.h> 
#include <conio.h>

#include "core/Library/LibraryManager.h"
#include "core/Document/PrintedDocument.h"
#include "core/Document/ElectronicDocument.h"
#include "core/utils/Constants.h"

using namespace std;
using namespace LibraryCore;
using namespace LibraryCore::Constants;

// --- КОЛЬОРИ ---
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

void SetColor(int text, int bg = 0) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

void ClearInput() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


// --- МЕНЮ ---
void PrintItem(int num, string text) {
    SetColor(YELLOW); cout << " " << num << ". ";
    SetColor(WHITE); cout << text << endl;
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

    cout << "\n[2. ПРАВИЛА ВВОДУ]" << endl;
    SetColor(YELLOW); cout << " - Текстові поля:"; SetColor(WHITE); cout << " Можна вводити з пробілами." << endl;
    SetColor(YELLOW); cout << " - ID:"; SetColor(WHITE); cout << " Мають бути унікальними." << endl;

    cout << "\n[3. ОПИС КОМАНД]" << endl;
    cout << " * Видача: Книга закріплюється за студентом на 14 днів." << endl;
    cout << " * Боржники: Показує список прострочених книг." << endl;

    if (true) {
        SetColor(LIGHTRED);
        cout << "\n[4. АДМІНІСТРАТОР]" << endl;
        cout << " Логін: admin | Пароль: admin123" << endl;
    }
    SetColor(LIGHTGREEN); cout << "============================================================" << endl; SetColor(WHITE);

    cout << "\nНатисніть Enter, щоб повернутися...";
    cin.get(); // Чекаємо натискання
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    LibraryManager app;
    string username, password;
    bool loggedIn = false;

    // --- АВТОРИЗАЦІЯ ---
    while (!loggedIn) {
        system("cls");
        SetColor(YELLOW); cout << "\n>>> ВХІД У СИСТЕМУ <<<" << endl;
        SetColor(DARKGRAY); cout << "(Default: admin / admin123)" << endl;
        SetColor(WHITE);

        // Логін і пароль — будь-які символи (ANY)
        if (!ReadString(" Логін", username, ANY)) continue;
        if (!ReadString(" Пароль", password, ANY, true)) continue;

        if (app.Login(username, password)) {
            loggedIn = true;
            SetColor(GREEN); cout << "\n " << MSG_LOGIN_SUCCESS << endl;
            Sleep(1000);
        }
        else {
            SetColor(RED); cout << "\n " << ERR_LOGIN_FAILED << endl;
            SetColor(WHITE);

            string choice;
            if (!ReadString(" Спробувати ще раз? (y/n)", choice, ANY)) continue;
            if (choice == "n" || choice == "N") return 0;
        }
    }

    // --- ГОЛОВНИЙ ЦИКЛ ---
    while (true) {
        bool isAdmin = false;
        if (app.GetCurrentUser())
            isAdmin = app.GetCurrentUser()->IsAdmin();

        ShowMenu(isAdmin);

        int choice;
        if (!ReadValue(" Ваш вибір", choice, DIGITS_ONLY))
            continue;

        system("cls");
        cout << endl;

        switch (choice) {
        case 0:
            app.Logout();
            SetColor(GREEN); cout << MSG_BYE << endl;
            return 0;

        case 1: { // Пошук
            string query;
            if (!ReadString(" Введіть частину назви або автора", query, ANY)) break;
            auto results = app.SearchDocuments(query);

            SetColor(CYAN);
            cout << "\n Знайдено документів: " << results.size() << endl;
            SetColor(WHITE);

            for (auto* doc : results)
                doc->DisplayInfo();

            break;
        }

        case 2: { // Видача
            string cId;
            int dId;

            if (!ReadString(" ID картки студента", cId, DIGITS_ONLY)) break;
            if (!ReadValue(" ID документа", dId, DIGITS_ONLY)) break;

            if (app.CheckoutBook(cId, dId)) {
                SetColor(GREEN); cout << " Успіх!\n";
            }
            else {
                SetColor(RED); cout << " Помилка видачі.\n";
            }
            break;
        }

        case 3: { // Повернення
            string cId;
            int dId;

            if (!ReadString(" ID картки студента", cId, DIGITS_ONLY)) break;
            if (!ReadValue(" ID документа", dId, DIGITS_ONLY)) break;

            if (app.ReturnBook(cId, dId)) {
                SetColor(GREEN); cout << " Успіх!\n";
            }
            else {
                SetColor(RED); cout << " Помилка повернення.\n";
            }
            break;
        }

        case 4:
            app.DisplayDebtorList();
            break;

        case 5: { // Додавання студента
            cout << "--- НОВИЙ СТУДЕНТ ---" << endl;

            string l, f, r, g, cId;
            int c;

            if (!ReadString(" Прізвище", l, TEXT_ONLY)) break;
            if (!ReadString(" Ім'я", f, TEXT_ONLY)) break;
            if (!ReadString(" Залікова", r, ANY)) break;
            if (!ReadValue(" Курс (1-6)", c, DIGITS_ONLY)) break;
            if (!ReadString(" Група", g, ANY)) break;
            if (!ReadString(" Читацький ID", cId, ANY)) break;

            app.AddStudent(Student(l, f, r, c, g, cId));
            break;
        }

        case 6: { // Додавання документа
            int type;
            if (!ReadValue(" Тип? (1-Книга, 2-Файл)", type, DIGITS_ONLY)) break;

            string t, a;
            int y;

            if (!ReadString(" Назва", t, ANY)) break;
            if (!ReadString(" Автор", a, TEXT_ONLY)) break;
            if (!ReadValue(" Рік (1000-2030)", y, DIGITS_ONLY)) break;

            if (type == 1) {
                int p;
                string m;

                if (!ReadValue(" Сторінок", p, DIGITS_ONLY)) break;
                if (!ReadString(" Палітурка", m, ANY)) break;

                app.AddDocument(make_unique<PrintedDocument>(0, t, a, y, p, m));
            }
            else {
                string f;
                double s;

                if (!ReadString(" Формат (PDF/EPUB)", f, ANY)) break;
                if (!ReadValue(" Розмір (MB)", s, DOUBLE_ONLY)) break;

                app.AddDocument(make_unique<ElectronicDocument>(0, t, a, y, f, s));
            }

            break;
        }

        case 7: {
            int id;
            if (!ReadValue(" ID для видалення", id, DIGITS_ONLY)) break;
            app.DeleteDocument(id);
            break;
        }

        case 8: { // Редагування студента
            string id;
            if (!ReadString(" Введіть ID картки студента", id, ANY)) break;

            cout << "--- Введіть нові дані ---" << endl;

            string l, f, r, g;
            int c;

            if (!ReadString(" Прізвище", l, TEXT_ONLY)) break;
            if (!ReadString(" Ім'я", f, TEXT_ONLY)) break;
            if (!ReadString(" Залікова", r, ANY)) break;
            if (!ReadValue(" Курс (1-6)", c, DIGITS_ONLY)) break;
            if (!ReadString(" Група", g, ANY)) break;

            app.EditStudent(id, Student(l, f, r, c, g, id));
            break;
        }

        case 9: { // Редагування документа
            int id;
            if (!ReadValue(" Введіть ID документа", id, DIGITS_ONLY)) break;

            cout << "--- Введіть нові дані ---" << endl;

            string t, a;
            int y;

            if (!ReadString(" Назва", t, ANY)) break;
            if (!ReadString(" Автор", a, TEXT_ONLY)) break;
            if (!ReadValue(" Рік", y, DIGITS_ONLY)) break;

            PrintedDocument tmp(id, t, a, y, 0, "");
            app.EditDocument(id, tmp);

            break;
        }

        case 10:
            app.SortDocumentsByTitle();
            break;

        case 11: {
            int t;
            if (!ReadValue(" Показати (1-Книги, 2-Файли)", t, DIGITS_ONLY)) break;

            auto v = app.FilterDocumentsByType((t == 1) ? "Printed" : "Electronic");
            for (auto* d : v) d->DisplayInfo();
            break;
        }

        case 12:
            app.DisplayStudents();
            break;

        case 13:
            app.DisplayDocuments();
            break;

        case 14:
            ShowHelp();
            break;

        case 15: {
            if (!isAdmin) break;

            string u, p;
            int a;

            if (!ReadString(" Новий Логін", u, ANY)) break;
            if (!ReadString(" Новий Пароль", p, ANY, true)) break;
            if (!ReadValue(" Права адміна? (1-Так, 0-Ні)", a, DIGITS_ONLY)) break;

            app.RegisterUser(u, p, (a == 1));
            break;
        }

        case 16: {
            if (!isAdmin) break;

            string u;
            if (!ReadString(" Логін для видалення", u, ANY)) break;
            app.DeleteUser(u);
            break;
        }

        case 17:
            if (isAdmin) app.DisplayUserList();
            break;

        default:
            SetColor(RED);
            cout << ERR_INVALID_CHOICE << endl;
        }

        SetColor(DARKGRAY);
        cout << "\n[Натисніть Enter щоб продовжити]";
        SetColor(WHITE);

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return 0;
}
