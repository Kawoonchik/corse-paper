#include "User.h"
#include <sstream>
#include <vector>

using std::string;

namespace LibraryCore
{
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

    // Конструктори

    User::User() : isAdmin(false) {}

    User::User(const string& username, const string& password, bool isAdmin)
        : username(username), password(password), isAdmin(isAdmin)
    {
    }

	// Методи Get/Set

    string User::GetUsername() const { return username; }
    string User::GetPassword() const { return password; }
    bool User::IsAdmin() const { return isAdmin; }

    void User::SetUsername(const string& name) { username = name; }
    void User::SetPassword(const string& pass) { password = pass; }
    void User::SetIsAdmin(bool status) { isAdmin = status; }

    // CSV методи 

    string User::ToCsv() const
    {
        std::stringstream ss;
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
            isAdmin = (tokens[2] == "1");
        }
    }
}