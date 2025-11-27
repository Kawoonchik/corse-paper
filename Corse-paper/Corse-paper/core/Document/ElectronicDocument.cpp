#include "ElectronicDocument.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <utility>

using std::string;
using std::cout;
using std::endl;

namespace LibraryCore
{
    ElectronicDocument::ElectronicDocument() : Document(), fileSizeMB(0.0) {}

    ElectronicDocument::ElectronicDocument(
        int id,
        const string& t,
        const string& a,
        int y,
        const string& f,
        double s
    )
        : Document(id, t, a, y), fileFormat(f), fileSizeMB(s)
    {
    }

    ElectronicDocument::~ElectronicDocument() 
    {
        // cout << " Електронний документ знищено: " << title << endl;
    }

	// Копіювання і переміщення

    ElectronicDocument::ElectronicDocument(const ElectronicDocument& other)
        : Document(other), fileFormat(other.fileFormat), fileSizeMB(other.fileSizeMB)
    {
    }

    ElectronicDocument& ElectronicDocument::operator=(const ElectronicDocument& other)
    {
        if (this == &other) return *this;
        Document::operator=(other);
        fileFormat = other.fileFormat;
        fileSizeMB = other.fileSizeMB;
        return *this;
    }

    ElectronicDocument::ElectronicDocument(ElectronicDocument&& other) noexcept
        : Document(std::move(other))
        , fileFormat(std::move(other.fileFormat))
        , fileSizeMB(other.fileSizeMB)
    {
        other.fileSizeMB = 0.0;
    }

    ElectronicDocument& ElectronicDocument::operator=(ElectronicDocument&& other) noexcept
    {
        if (this == &other) return *this;
        Document::operator=(std::move(other));
        fileFormat = std::move(other.fileFormat);
        fileSizeMB = other.fileSizeMB;
        other.fileSizeMB = 0.0;
        return *this;
    }

	// Методи Get/Set

    void ElectronicDocument::SetFileFormat(const string& f) { fileFormat = f; }
    string ElectronicDocument::GetFileFormat() const { return fileFormat; }

    void ElectronicDocument::SetFileSizeMB(double s) { fileSizeMB = s; }
    double ElectronicDocument::GetFileSizeMB() const { return fileSizeMB; }

    string ElectronicDocument::GetType() const { return "Electronic"; }

    string ElectronicDocument::GetDetails() const
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << fileSizeMB;
        return fileFormat + ", " + ss.str() + " MB";
    }

    void ElectronicDocument::DisplayInfo() const
    {
        Document::DisplayInfo();
        cout << " | [E-BOOK] " << GetDetails() << endl;
    }

    string ElectronicDocument::ToCsv() const
    {
        std::stringstream ss;
        ss << fileSizeMB;
        return Document::ToCsv() + ";" + fileFormat + ";" + ss.str();
    }

    void ElectronicDocument::FromCsv(const string& line)
    {
        Document::FromCsv(line);
        auto tokens = SplitCsvLine(line);
        if (tokens.size() >= 6) {
            fileFormat = tokens[4];
            try { fileSizeMB = std::stod(tokens[5]); }
            catch (...) { fileSizeMB = 0.0; }
        }
    }
}