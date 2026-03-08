#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>
#include <sstream>
#include <iomanip>

enum class Type
{
    expense,
    income,
};

enum Month 
{
    january = 1,
    february,
    march,
    april,
    may,
    june,
    july,
    august,
    september,
    october,
    november,
    december,
};

inline std::string monthToString(Month month)
{
    switch(month)
    {
        case january: return std::string("January");
        case february: return std::string("February");
        case march: return std::string("March");
        case april: return std::string("April");
        case may: return std::string("May");
        case june: return std::string("June");
        case july: return std::string("July");
        case august: return std::string("August");
        case september: return std::string("September");
        case october: return std::string("October");
        case november: return std::string("November");
        case december: return std::string("December");
        default: return std::string("");
    }
}

struct Date
{
    int day;
    Month month;
    int year;

    std::string toString() const 
    {
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << day << "-" << std::setw(2) << std::setfill('0') << month;
        
        return ss.str();
    }
};

struct Expense 
{
    Type type; // Income or expense
    std::string category;
    std::string description;
    double amount;
    Date date; 
};

inline std::string getExpenseTitle(int cols)
{
    int date = 5;
    int description = 25;
    int category = 25;
    int amount = cols - date - description - category - 4;

    std::stringstream ss;
    ss << std::setw(date) << "Date" << std::setw(description) << "Description" << std::setw(category) << "Category" << std::setw(amount) << "Amount";

    return ss.str();
}

#endif
