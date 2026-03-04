#include "window.h"
#include "app.h"
#include "expense.h"
#include <cmath>
#include <ncurses.h>


ListWindow::ListWindow(int h, int w)
    : m_title("Expense tracker")
{  
    init_pair(1, COLOR_WHITE, COLOR_BLUE);   // White font, blue bg
    init_pair(2, COLOR_RED, -1);             // Red font, default bg
    init_pair(3, COLOR_GREEN, -1);           // Green font, default bg
    init_pair(4, -1, COLOR_WHITE);           // Default font, white bg
    init_pair(5, -1, COLOR_RED);             // Default font, red bg 
    init_pair(6, -1, COLOR_GREEN);           // Default font, green bg 

    getmaxyx(stdscr, m_height, m_width);

    m_outerWindow = newwin(m_height, m_width, 0, 0);
    m_centerWindow = derwin(m_outerWindow, m_height - 2, m_width, 2, 0);

    //keypad(mainWin, TRUE);
}


void ListWindow::draw(const State& state)
{   
    werase(m_outerWindow);
    werase(m_centerWindow);

    
    drawCenterWindow(state);

    // Draw top panel
    wattron(m_outerWindow, A_BOLD);
    wattron(m_outerWindow, COLOR_PAIR(1));    
    for(int i = 0; i < 3; i++)
    {
        mvwhline(m_outerWindow, i, 0, ' ', m_width);
    }
    mvwprintw(m_outerWindow, 1, m_width / 2 - m_title.length() / 2, "%s", m_title.c_str());
    wattroff(m_outerWindow, COLOR_PAIR(1));
    wattroff(m_outerWindow, A_BOLD);

    // Draw bottom panel
    wattron(m_outerWindow, COLOR_PAIR(1));
    mvwhline(m_outerWindow, m_height - 1, 0, ' ', m_width);
    drawInfo();
    wattroff(m_outerWindow, COLOR_PAIR(1));

    update();
}


void ListWindow::update()
{
    wrefresh(m_outerWindow);
    wrefresh(m_centerWindow);
}


void ListWindow::drawCommands()
{   
    wattron(m_outerWindow, A_BOLD);
    mvwprintw(m_outerWindow, m_height - 1, 1, "  (N) New  ");   
    wprintw(m_outerWindow, "(D) Delete  ");
    wprintw(m_outerWindow, "(E) Edit  ");
    wprintw(m_outerWindow, "(Q) Quit  ");
    wattroff(m_outerWindow, A_BOLD);
}


void ListWindow::drawInfo()
{
    drawCommands();
    wprintw(m_outerWindow, "Page: 1");
}


void ListWindow::drawCenterWindow(const State& state) const
{   
    wattron(m_centerWindow, A_BOLD);
    mvwprintw(m_centerWindow, 1, 1, "%s", getExpenseTitle(m_width).c_str());
    wattroff(m_centerWindow, A_BOLD);
    mvwhline(m_centerWindow, 2, 1, ACS_HLINE, m_width - 2);
    
    // Draw all the expenses
    for(int i = 0; i < state.expenses.size(); i++)
    {   
        
        if(i == state.highlight) 
        {   
            wattron(m_centerWindow, A_REVERSE);
            mvwhline(m_centerWindow, i + 3, 1, ' ', m_width);
        }

        mvwprintw(m_centerWindow, i + 3, 2, "%s", state.expenses.at(i).date.toString().c_str());
        mvwprintw(m_centerWindow, i + 3, 20, "%s", state.expenses.at(i).description.c_str());
        mvwprintw(m_centerWindow, i + 3, 48, "%s", state.expenses.at(i).category.c_str());

        std::string amountStr = std::to_string(state.expenses.at(i).amount);

        if(state.expenses.at(i).type == Type::income)
        {
            if(i == state.highlight) wattron(m_centerWindow, COLOR_PAIR(6));
            else wattron(m_centerWindow, COLOR_PAIR(3));
            mvwprintw(m_centerWindow, i + 3, m_width - amountStr.length(), "+%.2f", state.expenses.at(i).amount);
        }
        else if(state.expenses.at(i).type == Type::expense)
        {
            if(i == state.highlight) wattron(m_centerWindow, COLOR_PAIR(5));
            else wattron(m_centerWindow, COLOR_PAIR(2));
            mvwprintw(m_centerWindow, i + 3, m_width - amountStr.length(), "-%.2f", state.expenses.at(i).amount);
        }
        wattroff(m_centerWindow, COLOR_PAIR(2) | COLOR_PAIR(3) | COLOR_PAIR(5) | COLOR_PAIR(6) | A_REVERSE);
    }

    mvwhline(m_centerWindow, m_height - 5, 1, ACS_HLINE, m_width - 2);
    wattron(m_centerWindow, A_BOLD);
    mvwprintw(m_centerWindow, m_height - 4, 48, "Total:");
    std::string totalStr = std::to_string(state.total);
    mvwprintw(m_centerWindow, m_height - 4, m_width - totalStr.length() + 1, "%.2f", state.total);
    wattroff(m_centerWindow, A_BOLD);
}


















