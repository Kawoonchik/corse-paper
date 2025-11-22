#include "BookRecord.h"
#include <sstream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::stringstream;

namespace LibraryCore
{
    static vector<string> SplitCsvLineRecord(const string& line, char delimiter = ';')
    {
        vector<string> tokens;
        string token;
        stringstream ss(line);
        while (std::getline(ss, token, delimiter))
        {
            tokens.push_back(token);
        }
        return tokens;
    }

    string BookRecord::ToCsv() const
    {
        stringstream ss;
        ss << documentId << ";"
            << readerCardId << ";"
            << issueDate << ";"
            << dueDate;
        return ss.str();
    }

    void BookRecord::FromCsv(const string& line)
    {
        auto tokens = SplitCsvLineRecord(line);
        if (tokens.size() >= 4)
        {
            try { documentId = std::stoi(tokens[0]); }
            catch (...) { documentId = 0; }
            readerCardId = tokens[1];
            try { issueDate = std::stoll(tokens[2]); }
            catch (...) { issueDate = 0; }
            try { dueDate = std::stoll(tokens[3]); }
            catch (...) { dueDate = 0; }
        }
    }
}