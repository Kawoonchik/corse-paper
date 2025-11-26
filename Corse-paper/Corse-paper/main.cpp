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
#include "core/utils/InputValidation.h" 

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

    SetColor(YELLOW); cout << "1."; SetColor(WHITE); cout << " Пошук документів" << endl;
    SetColor(YELLOW); cout << "2."; SetColor(WHITE); cout << " Видати книгу" << endl;
    SetColor(YELLOW); cout << "3."; SetColor(WHITE); cout << " Прийняти книгу" << endl;
    SetColor(YELLOW); cout << "4."; SetColor(WHITE); cout << " Список боржників" << endl;

    SetColor(DARKGRAY); cout << "----------------------------------------" << endl;
    SetColor(YELLOW); cout << "5."; SetColor(WHITE); cout << " Додати студента" << endl;
    SetColor(YELLOW); cout << "6."; SetColor(WHITE); cout << " Додати документ" << endl;
    SetColor(YELLOW); cout << "7."; SetColor(WHITE); cout << " Видалити документ" << endl;

    SetColor(DARKGRAY); cout << "----------------------------------------" << endl;
    SetColor(YELLOW); cout << "8."; SetColor(WHITE); cout << " [РЕДАГУВАННЯ] Змінити дані студента" << endl;
    SetColor(YELLOW); cout << "9."; SetColor(WHITE); cout << " [РЕДАГУВАННЯ] Змінити дані документа" << endl;
    SetColor(YELLOW); cout << "10."; SetColor(WHITE); cout << " [СОРТУВАННЯ] Сортувати документи" << endl;
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
        SetColor(YELLOW); cout << "17."; SetColor(WHITE); cout << " Список користувачів" << endl;
    }

    SetColor(DARKGRAY);
    cout << "----------------------------------------" << endl;
    SetColor(YELLOW); cout << "0."; SetColor(WHITE); cout << " Вихід" << endl;
    SetColor(LIGHTCYAN);
    cout << "========================================" << endl;
    SetColor(WHITE);
    // Видалив "Ваш вибір: ", бо функція вводу сама виведе запит
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

    cout << "\n" << TXT_PRESS_ANY_KEY;
    _getch();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    EnableAnsiSupport();

    LibraryManager app;
    InputValidation inputVal;

    string username, password;
    bool loggedIn = false;

    // --- АВТОРИЗАЦІЯ ---
    while (!loggedIn) {
        system("cls");
        SetColor(YELLOW); cout << "\n>>> ВХІД У СИСТЕМУ <<<" << endl;
        SetColor(DARKGRAY); cout << "(Default: admin / admin123)" << endl; SetColor(WHITE);

        username = inputVal.GetStringInput(" Логін:", ValidationMode::TEXT_ONLY);
        password = inputVal.GetStringInput(" Пароль:", ValidationMode::ANY);

        if (app.Login(username, password)) {
            loggedIn = true;
            SetColor(GREEN); cout << "\n " << MSG_LOGIN_SUCCESS << endl; Sleep(1000);
        }
        else {
            SetColor(RED); cout << "\n " << ERR_LOGIN_FAILED << endl; SetColor(WHITE);

            string choice = inputVal.GetStringInput(" Спробувати ще раз? (y/n)");
            if (choice == "n" || choice == "N") return 0;
        }
    }

    // --- ГОЛОВНИЙ ЦИКЛ ---
    while (true) {
        bool isAdmin = (app.GetCurrentUser() ? app.GetCurrentUser()->IsAdmin() : false);

        ShowMenu(isAdmin);
        int choice = inputVal.GetIntInput(" Ваш вибір:", 0, 9999);

        system("cls");
        cout << endl;

        switch (choice) {

        case 0:
            app.Logout();
            SetColor(GREEN); cout << MSG_BYE << endl;
            return 0;

        case 1: { // Пошук
            string query = inputVal.GetStringInput(" Введіть частину назви або автора:", ValidationMode::TEXT_ONLY);
            auto results = app.SearchDocuments(query);
            SetColor(CYAN); cout << "\n Знайдено документів: " << results.size() << endl; SetColor(WHITE);
            for (auto* doc : results) doc->DisplayInfo();
            break;
        }

        case 2: {// Видача
            string cId = inputVal.GetStringInput(" ID картки студента:", ValidationMode::ANY);
            int dId = inputVal.GetIntInput(" ID документа:", 0, 999999);
            if (app.CheckoutBook(cId, dId)) { SetColor(GREEN); cout << " Успіх!\n"; }
            else { SetColor(RED); cout << " Помилка видачі.\n"; }
            break;
        }

        case 3: {// Повернення
            string cId = inputVal.GetStringInput(" ID картки студента:", ValidationMode::ANY);
            int dId = inputVal.GetIntInput(" ID документа:", 0, 999999);
            if (app.ReturnBook(cId, dId)) { SetColor(GREEN); cout << " Успіх!\n"; }
            else { SetColor(RED); cout << " Помилка повернення.\n"; }
            break;
        }

        case 4:
            app.DisplayDebtorList();
            break;

        case 5: {// Додавання студента
            cout << "--- НОВИЙ СТУДЕНТ ---" << endl;

            string l = inputVal.GetStringInput(" Прізвище:", ValidationMode::TEXT_ONLY);
            string f = inputVal.GetStringInput(" Ім'я:", ValidationMode::TEXT_ONLY);
            string r = inputVal.GetStringInput(" Залікова:", ValidationMode::ANY);
            int c = inputVal.GetIntInput(" Курс:", 1, 6);
            string g = inputVal.GetStringInput(" Група:", ValidationMode::ANY);
            string cId = inputVal.GetStringInput(" Читацький ID:", ValidationMode::ANY);

            app.AddStudent(Student(l, f, r, c, g, cId));
            break;
        }

        case 6: { // Додавання документа
            int type = inputVal.GetIntInput(" Тип? (1-Книга, 2-Файл):", 1, 2);
            string t = inputVal.GetStringInput(" Назва:", ValidationMode::TEXT_ONLY);
            string a = inputVal.GetStringInput(" Автор:", ValidationMode::TEXT_ONLY);
            int y = inputVal.GetIntInput(" Рік:", 0, 2100);

            if (type == 1) {
                int p = inputVal.GetIntInput(" Сторінок:", 1, 10000);
                string m = inputVal.GetStringInput(" Палітурка:", ValidationMode::TEXT_ONLY);
                app.AddDocument(make_unique<PrintedDocument>(0, t, a, y, p, m));
            }
            else {
                string f = inputVal.GetStringInput(" Формат (PDF/EPUB):", ValidationMode::ANY);
                double s = inputVal.GetDoubleInput(" Розмір (MB):", 0.1, 100000);
                app.AddDocument(make_unique<ElectronicDocument>(0, t, a, y, f, s));
            }
            break;
        }

		case 7: { // Видалення документа
            int id = inputVal.GetIntInput(" ID для видалення:", 0, 999999);
            app.DeleteDocument(id);
            break;
        }

		case 8: { // Редагування студента
            string id = inputVal.GetStringInput(" Введіть ID картки студента:", ValidationMode::ANY);
            cout << "--- Введіть нові дані ---" << endl;

            string l = inputVal.GetStringInput(" Прізвище:", ValidationMode::TEXT_ONLY);
            string f = inputVal.GetStringInput(" Ім'я:", ValidationMode::TEXT_ONLY);
            string r = inputVal.GetStringInput(" Залікова:", ValidationMode::ANY);
            int c = inputVal.GetIntInput(" Курс:", 1, 6);
            string g = inputVal.GetStringInput(" Група:", ValidationMode::ANY);

            app.EditStudent(id, Student(l, f, r, c, g, id));
            break;
        }

		case 9: { // Редагування документа
            int id = inputVal.GetIntInput(" Введіть ID документа:", 0, 999999);
            cout << "--- Введіть нові дані ---" << endl;

            string t = inputVal.GetStringInput(" Назва:", ValidationMode::TEXT_ONLY);
            string a = inputVal.GetStringInput(" Автор:", ValidationMode::TEXT_ONLY);
            int y = inputVal.GetIntInput(" Рік:", 0, 2100);

            PrintedDocument tmp(id, t, a, y, 0, "");
            app.EditDocument(id, tmp);
            break;
        }

        case 10:
            app.SortDocumentsByTitle();
            break;

		case 11: { // Фільтр за типом
            int t = inputVal.GetIntInput(" Показати (1-Книги, 2-Файли):", 1, 2);
            string typeStr = (t == 1 ? "Printed" : "Electronic");
            auto v = app.FilterDocumentsByType(typeStr);
            for (auto* d : v) d->DisplayInfo();
            break;
        }

        case 12: app.DisplayStudents(); break;
        case 13: app.DisplayDocuments(); break;
        case 14: ShowHelp(); break;

		case 15: { // Реєстрація користувача
            if (!isAdmin) break;
            string u = inputVal.GetStringInput(" Новий Логін:", ValidationMode::TEXT_ONLY);
            string p = inputVal.GetStringInput(" Новий Пароль:", ValidationMode::ANY);
            int a = inputVal.GetIntInput(" Права адміна? (1-Так, 0-Ні):", 0, 1);
            app.RegisterUser(u, p, (a == 1));
            break;
        }

		case 16: { // Видалення користувача
            if (!isAdmin) break;
            string u = inputVal.GetStringInput(" Логін для видалення:", ValidationMode::TEXT_ONLY);
            app.DeleteUser(u);
            break;
        }

		case 17: // Список користувачів
            if (isAdmin) app.DisplayUserList();
            break;

        default:
            SetColor(RED); cout << ERR_INVALID_CHOICE << endl;
        }

        SetColor(DARKGRAY);
        cout << "\n" << TXT_PRESS_ANY_KEY;
        SetColor(WHITE);
        _getch();
    }

    return 0;
}
