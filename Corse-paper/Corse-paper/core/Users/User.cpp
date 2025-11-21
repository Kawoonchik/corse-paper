#include "User.h"
#include <sstream>
#include <vector>

using std::string;

namespace LibraryCore
{
    // Допоміжний метод для розбиття рядка CSV (схожий на той, що був у Document)
    namespace
    {
        std::vector<string> SplitCsvLine(const string& line, char delimiter = ';')
        {
            std::vector<string> tokens;
            string token;
            std::stringstream ss(line);
            while (std::getline(ss, token, delimiter))
            {
                tokens.push_back(token);
            }
            return tokens;
        }
    }

    // --- 1. Конструктори ---

    User::User() : isAdmin(false) {}

    User::User(const string& username, const string& password, bool isAdmin)
        : username(username), password(password), isAdmin(isAdmin)
    {
    }

    // --- 2. Getters ---

    string User::GetUsername() const { return username; }
    string User::GetPassword() const { return password; }
    bool User::IsAdmin() const { return isAdmin; }

    // --- 3. Setters ---

    void User::SetUsername(const string& name) { username = name; }
    void User::SetPassword(const string& pass) { password = pass; }
    void User::SetIsAdmin(bool status) { isAdmin = status; }

    // --- 4. CSV методи ---

    string User::ToCsv() const
    {
        std::stringstream ss;
        // Перетворюємо bool на 1 або 0
        ss << username << ";" << password << ";" << (isAdmin ? "1" : "0");
        return ss.str();
    }

    void User::FromCsv(const string& line)
    {
        auto tokens = SplitCsvLine(line);

        if (tokens.size() >= 3)
        {
            username = tokens[0];
            password = tokens[1];
            // 1 -> true, 0 -> false
            isAdmin = (tokens[2] == "1");
        }
    }
}