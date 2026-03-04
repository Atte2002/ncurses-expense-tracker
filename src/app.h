#ifndef APP_H
#define APP_H

#include "window.h"
#include "expense.h"
#include <memory>
#include <vector>

struct State
{
    std::vector<Expense> expenses;
    int highlight = 0;

    enum class Window
    {
        List,
        Add,
        Overview
    };

    Window current = Window::List;
    bool running = true;
    double total = 0;
};

class App 
{
public:
    void init();
    void end();
    void run();
private:
    State m_state;
    std::unique_ptr<ListWindow> m_listWindow;
    std::unique_ptr<AddWindow> m_addWindow;
    std::unique_ptr<OverviewWindow> m_overviewWindow;

    void draw();
    void readCSV();
    void handleInput(int ch);
};

#endif
