#include "PrintedDocument.h"
#include <iostream> 
#include <utility> 

using std::string;

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

    PrintedDocument::~PrintedDocument() {}

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
        : Document(std::move(other)) 
        , pageCount(other.pageCount)
        , medium(std::move(other.medium))
    {
        other.pageCount = 0;
    }

    PrintedDocument& PrintedDocument::operator=(PrintedDocument&& other) noexcept
    {
        if (this == &other) return *this;

        Document::operator=(std::move(other)); 
        pageCount = other.pageCount;
        medium = std::move(other.medium);

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
        return std::to_string(pageCount) + " pages, " + medium;
    }

    void PrintedDocument::DisplayInfo() const
    {
        Document::DisplayInfo();
        std::cout << " | [BOOK] " << GetDetails() << std::endl;
    }

    string PrintedDocument::ToCsv() const
    {
        return Document::ToCsv() + ";" + std::to_string(pageCount) + ";" + medium;
    }

    void PrintedDocument::FromCsv(const std::string& line)
    {
        Document::FromCsv(line); 

        auto tokens = this->SplitCsvLine(line);
        if (tokens.size() >= 6)
        {
            try { pageCount = std::stoi(tokens[4]); }
            catch (...) { pageCount = 0; }
            medium = tokens[5];
        }
    }
}