#pragma once
#include "ElectronicDocument.h"
#include <iostream>
#include <sstream>
#include <iomanip> // Для setprecision
#include <utility> // Для std::move

using std::string;
using std::cout;
using std::endl;

namespace LibraryCore
{

        /** @brief Конструктор за замовчуванням. */
        ElectronicDocument::ElectronicDocument()
            : Document(), fileSizeMB(0.0)
        {
        }

        /**
         * @brief Конструктор з параметрами.
         * @param id - Унікальний ідентифікатор документа.
         * @param title - Назва документа.
         * @param author - Автор.
         * @param year - Рік видання.
         * @param format - Формат електронного файлу (наприклад, "PDF").
         * @param size - Розмір файлу у мегабайтах.
         */
        ElectronicDocument::ElectronicDocument(int id, const string& t, const string& a, int y, const string& f, double s)
            : Document(id, t, a, y), fileFormat(f), fileSizeMB(s)
        {
        }

        ElectronicDocument::~ElectronicDocument()
        {
        }

        // Get/Set
        /** @brief Встановлює формат файлу. @param format - Новий формат файлу. */
        void ElectronicDocument::SetFileFormat(const string& f) { fileFormat = f; }

        /** @brief Повертає формат файлу. @return Формат файлу. */
        string ElectronicDocument::GetFileFormat() const { return fileFormat; }

        /** @brief Встановлює розмір файлу. @param size - Розмір файлу у МБ. */
        void ElectronicDocument::SetFileSizeMB(double s) { fileSizeMB = s; }   

        /** @brief Повертає розмір файлу. @return Розмір файлу у МБ. */
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
            Document::DisplayInfo(); // Виводимо ID, Назву, Автора
            cout << " | [E-BOOK] " << GetDetails() << endl;
        }

        // --- CSV Logic ---

        string ElectronicDocument::ToCsv() const
        {
            std::stringstream ss;
            ss << fileSizeMB;
            // Спочатку базові дані -> потім ; -> потім свої
            return Document::ToCsv() + ";" + fileFormat + ";" + ss.str();
        }

        void ElectronicDocument::FromCsv(const string& line)
        {
            // 1. Заповнюємо базові поля (ID, Title...)
            Document::FromCsv(line);

            // 2. Парсимо свої унікальні поля
            auto tokens = SplitCsvLine(line);
            // У базового 4 поля (0,1,2,3), тому наші починаються з 4
            if (tokens.size() >= 6)
            {
                fileFormat = tokens[4];
                try { fileSizeMB = std::stod(tokens[5]); }
                catch (...) { fileSizeMB = 0.0; }
            }
        }
   
}