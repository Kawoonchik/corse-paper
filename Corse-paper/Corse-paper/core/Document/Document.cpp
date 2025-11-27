#include "Document.h"
#include <sstream>

using std::string;
using std::cout;
using std::endl;

namespace LibraryCore
{
    Document::Document() : id(0), year(0) {}

    Document::Document(
        int id,
        const string& t,
        const string& a,
        int y
    )
        : id(id), title(t), author(a), year(y)
    {
    }

    Document::~Document() 
    {
        // cout << " Документ знищено: " << title << endl;
    }

    // Копіювання
    Document::Document(const Document& other)
        : id(other.id), title(other.title), author(other.author), year(other.year)
    {
    }

    Document& Document::operator=(const Document& other)
    {
        if (this == &other) return *this;
        id = other.id;
        title = other.title;
        author = other.author;
        year = other.year;
        return *this;
    }

    // Переміщення
    Document::Document(Document&& other) noexcept
        : id(other.id)
        , title(std::move(other.title))
        , author(std::move(other.author))
        , year(other.year)
    {
        other.id = 0;
        other.year = 0;
    }

    Document& Document::operator=(Document&& other) noexcept
    {
        if (this == &other) return *this; 


        id = other.id;
        title = std::move(other.title);
        author = std::move(other.author);
        year = other.year;

        other.id = 0;
        other.year = 0;

        return *this;
    }
        
	// Get/Set методи 
    void Document::SetId(int val) { id = val; }
    int Document::GetId() const { return id; }

    void Document::SetTitle(const string& val) { title = val; }
    string Document::GetTitle() const { return title; }

    void Document::SetAuthor(const string& val) { author = val; }
    string Document::GetAuthor() const { return author; }

    void Document::SetYear(int val) { year = val; }
    int Document::GetYear() const { return year; }

    void Document::DisplayInfo() const
    {
        cout << "ID: " << id << " | " << title << " (" << year << ") - " << author;
    }

    string Document::ToCsv() const
    {
        std::stringstream ss;
        ss << id << ";" << title << ";" << author << ";" << year;
        return ss.str();
    }

    std::vector<string> Document::SplitCsvLine(const string& line, char delimiter) const
    {
        std::vector<string> tokens;
        string token;
        std::stringstream ss(line);
        while (std::getline(ss, token, delimiter)) tokens.push_back(token);
        return tokens;
    }

    void Document::FromCsv(const string& line)
    {
        auto tokens = SplitCsvLine(line);
        if (tokens.size() >= 4)
        {
            try { id = std::stoi(tokens[0]); }
            catch (...) { id = 0; }
            title = tokens[1];
            author = tokens[2];
            try { year = std::stoi(tokens[3]); }
            catch (...) { year = 0; }
        }
    }
}