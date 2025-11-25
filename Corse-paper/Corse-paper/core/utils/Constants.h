#pragma once

namespace LibraryCore
{
    namespace Constants
    {
        // Файли даних 
        const char* const FILE_STUDENTS = "students.txt";
        const char* const FILE_DOCUMENTS = "documents.txt";
        const char* const FILE_USERS = "users.txt";
        const char* const FILE_TRANSACTIONS = "transactions.txt";

        // Повідомлення про успіх
        const char* const MSG_SUCCESS_REGISTERED = "Успіх: Користувача зареєстровано.";
        const char* const MSG_SUCCESS_DELETED_USER = "Успіх: Користувача видалено.";
        const char* const MSG_SUCCESS_ADDED_STUDENT = "Успіх: Студента додано.";
        const char* const MSG_SUCCESS_UPDATED_STUDENT = "Успіх: Дані студента оновлено.";
        const char* const MSG_SUCCESS_DELETED_STUDENT = "Успіх: Студента видалено.";
        const char* const MSG_SUCCESS_ADDED_DOC = "Успіх: Документ додано (ID: ";
        const char* const MSG_SUCCESS_UPDATED_DOC = "Успіх: Базові дані документа оновлено.";
        const char* const MSG_SUCCESS_DELETED_DOC = "Успіх: Документ видалено.";
        const char* const MSG_SUCCESS_CHECKOUT = "Успіх: Книгу видано.";
        const char* const MSG_SUCCESS_RETURN = "Успіх: Книгу повернуто.";
        const char* const MSG_SORTED = "Виконано: Список документів відсортовано за назвою.";
        const char* const MSG_LOGIN_SUCCESS = "Вхід успішний!";
        const char* const MSG_BYE = "Дані збережено. До побачення!";

        // Повідомлення про помилки
        const char* const ERR_USER_EXISTS = "Помилка: Користувач з таким логіном вже існує!";
        const char* const ERR_DELETE_SELF = "Помилка: Неможливо видалити власний акаунт.";
        const char* const ERR_USER_NOT_FOUND = "Помилка: Користувача не знайдено.";
        const char* const ERR_STUDENT_EXISTS = "Помилка: Студент з таким читацьким квитком вже існує.";
        const char* const ERR_STUDENT_NOT_FOUND = "Помилка: Студента не знайдено.";
        const char* const ERR_STUDENT_HAS_BOOKS = "Помилка: Неможливо видалити. Студент має неповернуті книги!";
        const char* const ERR_DOC_NOT_FOUND = "Помилка: Документ не знайдено.";
        const char* const ERR_DOC_CHECKED_OUT = "Помилка: Неможливо видалити. Документ зараз у читача.";
        const char* const ERR_DOC_ALREADY_ISSUED = "Помилка: Цей документ вже виданий.";
        const char* const ERR_TRANS_NOT_FOUND = "Помилка: Запис про видачу не знайдено (Студент не брав цю книгу).";
        const char* const ERR_LOGIN_FAILED = "Помилка: Невірний логін або пароль.";
        const char* const ERR_INPUT_NUMBER = "Помилка: Потрібно ввести число!";
        const char* const ERR_INVALID_CHOICE = "Невірний вибір.";
        const char* const ERR_ACCESS_DENIED = "Доступ заборонено.";
        const char* const ERR_GENERAL = "Помилка!";

        // Інтерфейс 
        const char* const TXT_CANCELLED = " >>> Операцію скасовано.";
        const char* const TXT_PRESS_ANY_KEY = "Натисніть будь-яку клавішу...";
        const char* const TXT_LIST_EMPTY = "Список пустий.";
        const char* const TXT_FUND_EMPTY = "Фонд пустий.";
        const char* const TXT_NO_DEBTORS = "Боржників немає.";
    }
}