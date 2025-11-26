#include "Student.h"
#include <sstream>  
#include <vector> 
#include <utility> 

using std::cout;
using std::endl;
using std::string;

namespace LibraryCore
{
    // Конструктори 

    Student::Student() : course(0)
    {
    }

    Student::Student(
        const string& lName,
        const string& fName,
        const string& recBook,
        int crs,
        const string& grp,
        const string& cardId
    )
        : lastName(lName)
        , firstName(fName)
        , recordBookNumber(recBook)
        , course(crs)
        , group(grp)
        , readerCardId(cardId)
    {
    }

    Student::~Student()
    {
        cout << " Студента знищено: " << lastName << endl;
    }

    // Методи копіювання і переміщення

    // Копіювання
    Student::Student(const Student& other)
        : lastName(other.lastName)
        , firstName(other.firstName)
        , recordBookNumber(other.recordBookNumber)
        , course(other.course)
        , group(other.group)
        , readerCardId(other.readerCardId)
    {
    }

    Student& Student::operator=(const Student& other)
    {
        if (this == &other) return *this;
        lastName = other.lastName;
        firstName = other.firstName;
        recordBookNumber = other.recordBookNumber;
        course = other.course;
        group = other.group;
        readerCardId = other.readerCardId;
        return *this;
    }

    // Переміщення
    Student::Student(Student&& other) noexcept
        : lastName(std::move(other.lastName))
        , firstName(std::move(other.firstName))
        , recordBookNumber(std::move(other.recordBookNumber))
        , course(other.course)
        , group(std::move(other.group))
        , readerCardId(std::move(other.readerCardId))
    {
        other.course = 0;
    }

    Student& Student::operator=(Student&& other) noexcept
    {
        if (this == &other) return *this;
        lastName = std::move(other.lastName);
        firstName = std::move(other.firstName);
        recordBookNumber = std::move(other.recordBookNumber);
        course = other.course;
        group = std::move(other.group);
        readerCardId = std::move(other.readerCardId);
        other.course = 0;
        return *this;
    }

    // Get/Set методи

    void Student::SetLastName(const string& val) { lastName = val; }
    string Student::GetLastName() const { return lastName; }

    void Student::SetFirstName(const string& val) { firstName = val; }
    string Student::GetFirstName() const { return firstName; }

    void Student::SetRecordBookNumber(const string& val) { recordBookNumber = val; }
    string Student::GetRecordBookNumber() const { return recordBookNumber; }

    void Student::SetCourse(int val) {
        if (val > 0 && val <= 6) course = val;
        else cout << "Error: Course must be 1-6" << endl;
    }
    int Student::GetCourse() const { return course; }

    void Student::SetGroup(const string& val) { group = val; }
    string Student::GetGroup() const { return group; }

    void Student::SetReaderCardId(const string& val) { readerCardId = val; }
    string Student::GetReaderCardId() const { return readerCardId; }

    // Власні методи

    string Student::GetFullName() const
    {
        return lastName + " " + firstName;
    }

    void Student::DisplayInfo() const
    {
        cout << "---------------------------------" << endl;
        cout << "Student:  " << GetFullName() << endl;
        cout << "Course:   " << course << " (" << group << ")" << endl;
        cout << "RecBook:  " << recordBookNumber << endl;
        cout << "Card ID:  " << readerCardId << endl;
        cout << "---------------------------------" << endl;
    }

    void Student::IncrementCourse()
    {
        if (course < 6) course++;
    }

    // CSV логіка 

    string Student::ToCsv() const
    {
        // Використовуємо ";" як розділювач
        std::stringstream ss;
        ss << lastName << ";"
            << firstName << ";"
            << recordBookNumber << ";"
            << course << ";"
            << group << ";"
            << readerCardId;
        return ss.str();
    }

    void Student::FromCsv(const string& line)
    {
        std::stringstream ss(line);
        string segment;
        std::vector<string> seglist;

        // Розбиваємо рядок по ";"
        while (std::getline(ss, segment, ';'))
        {
            seglist.push_back(segment);
        }

        if (seglist.size() >= 6)
        {
            lastName = seglist[0];
            firstName = seglist[1];
            recordBookNumber = seglist[2];
            try {
                course = std::stoi(seglist[3]);
            }
            catch (...) {
                course = 0;
            }
            group = seglist[4];
            readerCardId = seglist[5];
        }
    }
}