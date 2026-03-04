#ifndef WINDOW_H
#define WINDOW_H

#include "expense.h"
#include <ncurses.h>
#include <string>
#include <vector>

struct State;
class App;

class ListWindow
{
public:
    ListWindow(int h, int w);
    void draw(const State& state);    
    void end();
    void update();
    void scrollUp();
    void scrollDown();
private:
    std::string m_title;
    int m_width;
    int m_height;
    int m_startY;
    int m_startX;
    int m_scrollOffset;
    WINDOW* m_centerWindow;
    WINDOW* m_outerWindow;
    
    void drawCommands();
    void drawInfo();
    void drawCenterWindow(const State& state) const;
    void drawOuterWindow(const State& state) const;
};

class AddWindow
{
public:
private:
};

class OverviewWindow
{
public:
private:
};

#endif
