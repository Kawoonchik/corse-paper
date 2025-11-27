#include "PrintedDocument.h"
#include <iostream> 
#include <utility> 

using std::string;
using namespace std;

namespace LibraryCore
{
    PrintedDocument::PrintedDocument() : Document(), pageCount(0) {}

    PrintedDocument::PrintedDocument(
        int id,
        const string& t,
        const string& a,
        int y,
        int p,
        const string& m
    )
        : Document(id, t, a, y), pageCount(p), medium(m)
    {
    }

    PrintedDocument::~PrintedDocument() 
    {
       // cout << " Документ знищено: " << title << endl;
    }

	// Копіювання та переміщення
    PrintedDocument::PrintedDocument(const PrintedDocument& other)
        : Document(other) 
        , pageCount(other.pageCount)
        , medium(other.medium)
    {
    }

    PrintedDocument& PrintedDocument::operator=(const PrintedDocument& other)
    {
        if (this == &other) return *this;

        Document::operator=(other); 
        pageCount = other.pageCount;
        medium = other.medium;

        return *this;
    }

    PrintedDocument::PrintedDocument(PrintedDocument&& other) noexcept
        : Document(move(other)) 
        , pageCount(other.pageCount)
        , medium(move(other.medium))
    {
        other.pageCount = 0;
    }

    PrintedDocument& PrintedDocument::operator=(PrintedDocument&& other) noexcept
    {
        if (this == &other) return *this;

        Document::operator=(move(other)); 
        pageCount = other.pageCount;
        medium = move(other.medium);

        other.pageCount = 0;
        return *this;
    }

	// Get/Set методи
    void PrintedDocument::SetPageCount(int c) { pageCount = c; }
    int PrintedDocument::GetPageCount() const { return pageCount; }

    void PrintedDocument::SetMedium(const string& m) { medium = m; }
    string PrintedDocument::GetMedium() const { return medium; }

    string PrintedDocument::GetType() const { return "Printed"; }

    string PrintedDocument::GetDetails() const
    {
        return to_string(pageCount) + " pages, " + medium;
    }

    void PrintedDocument::DisplayInfo() const
    {
        Document::DisplayInfo();
        cout << " | [BOOK] " << GetDetails() << endl;
    }

    string PrintedDocument::ToCsv() const
    {
        return Document::ToCsv() + ";" + to_string(pageCount) + ";" + medium;
    }

    void PrintedDocument::FromCsv(const string& line)
    {
        Document::FromCsv(line); 

        auto tokens = this->SplitCsvLine(line);
        if (tokens.size() >= 6)
        {
            try { pageCount = stoi(tokens[4]); }
            catch (...) { pageCount = 0; }
            medium = tokens[5];
        }
    }
}