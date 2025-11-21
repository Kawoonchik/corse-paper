
#pragma once
#include <string>
#include <iostream>

namespace LibraryCore
{
    /**
     * @class User
     * @brief Клас для зберігання облікових даних користувачів.
     *
     * Містить логін, пароль та прапор адміністратора. Потрібен для реалізації
     * авторизації в системі.
     */
    class User
    {
    private:
        std::string username;
        std::string password;
        bool isAdmin;

    public:
        // --- 1. Конструктори та деструктор ---

        /** @brief Конструктор за замовчуванням. */
        User();

        /**
         * @brief Конструктор з параметрами.
         * @param username - Логін користувача.
         * @param password - Пароль користувача (зберігається у відкритому вигляді).
         * @param isAdmin - Прапор, чи є користувач адміністратором.
         */
        User(const std::string& username, const std::string& password, bool isAdmin);

        /** @brief Деструктор. */
        ~User() = default;

        // Rule of 5 (використовуємо default для простих полів)
        User(const User& other) = default;
        User& operator=(const User& other) = default;
        User(User&& other) noexcept = default;
        User& operator=(User&& other) noexcept = default;

        // --- 2. Getters ---
        /** @brief Повертає логін користувача. @return Логін. */
        std::string GetUsername() const;
        /** @brief Повертає пароль користувача. @return Пароль. */
        std::string GetPassword() const;
        /** @brief Перевіряє, чи є користувач адміністратором. @return true, якщо адміністратор. */
        bool IsAdmin() const;

        // --- 3. Setters ---
        /** @brief Встановлює логін користувача. @param username - Новий логін. */
        void SetUsername(const std::string& username);
        /** @brief Встановлює пароль користувача. @param password - Новий пароль. */
        void SetPassword(const std::string& password);
        /** @brief Встановлює статус адміністратора. @param isAdmin - Статус (true/false). */
        void SetIsAdmin(bool isAdmin);

        // --- 4. CSV методи ---

        /**
         * @brief Формує рядок CSV для запису у файл.
         * @return Рядок у форматі username;password;isAdmin
         */
        std::string ToCsv() const;

        /**
         * @brief Парсить рядок CSV і заповнює поля об'єкта.
         * @param line - Вхідний рядок CSV.
         */
        void FromCsv(const std::string& line);
    };
}