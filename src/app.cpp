#include "app.h"
#include "expense.h"
#include <fstream>
#include <memory>
#include <ncurses.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <locale.h>

void App::init()
{   
    setlocale(LC_ALL, "");
    readCSV();
    initscr();
    curs_set(0);
    start_color();
    use_default_colors();

    if(!has_colors())
    {
        endwin();
        return;
    }

    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    refresh(); 
}

void App::end()
{
    endwin();
}

void App::run()
{   
    init();
    m_listWindow = std::make_unique<ListWindow>(20, 40);

    while(m_state.running)
    {   
        int ch = getch();
        handleInput(ch);
        draw();
    }
    end();
}

void App::draw()
{
    m_listWindow->draw(m_state);
}

void App::readCSV()
{
    std::ifstream file("./expenses.csv");

    if(!file)
    {
        std::cerr << "Couldn't open file\n";
        return;
    }

    std::string line;
    std::getline(file, line);

    while(std::getline(file, line))
    {   
        std::stringstream ss(line);

        std::string temp;
        std::string typeStr;
        std::string category;
        std::string description;
        std::string dateStr;
 
        std::getline(ss, typeStr, ';');
        std::getline(ss, category, ';');
        std::getline(ss, description, ';');
        std::getline(ss, temp, ';');

        double amount = std::stod(temp);
        Type type = static_cast<Type>(std::stoi(typeStr));
        
        // Calculate total
        if(type == Type::income) m_state.total += amount;
        else m_state.total -= amount;
       
        Date date;
        std::getline(ss, dateStr, ';');
        std::stringstream ssDate(dateStr);
        
        // Parse date
        std::getline(ssDate, temp, '-');
        date.day = std::stoi(temp);
        std::getline(ssDate, temp, '-');
        date.month = std::stoi(temp);
        std::getline(ssDate, temp, '-');
        date.year = std::stoi(temp);
                
        m_state.expenses.emplace_back(type, category, description, amount, date);
    }
}

void App::handleInput(int ch)
{
    switch(ch) 
    {
        case 'q':
            m_state.running = false;
            break;
        case 'n':
            break;
        case 'd':
            break;
        case 'e':
            break;
        case KEY_DOWN:
            m_state.highlight++;
            break;
        case KEY_UP:
            m_state.highlight--;
            break;
    }  
}

