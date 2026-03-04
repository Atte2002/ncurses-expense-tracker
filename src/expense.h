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
    january,
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

struct Date
{
    int day;
    int month;
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
