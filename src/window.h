#ifndef WINDOW_H
#define WINDOW_H

#include <ncurses.h>
#include <string>

struct State;
class App;

class ListWindow
{
public:
    ListWindow(int h, int w);
    void draw(const State& state);    
    void end();
    void update(const State& state);
    void scrollUp();
    void scrollDown();
private:
    std::string m_title;
    int m_width;
    int m_height;
    int m_pageSize; // How many expenses can be fitted on one page
    int m_scrollOffset;
    int m_pageNum; 
    int m_row;
    WINDOW* m_centerWindow;
    WINDOW* m_outerWindow;
    
    void drawCommands();
    void drawInfo();
    void drawCenterWindow(const State& state);
    void drawOuterWindow(const State& state) const;
    void changePage(const State& state);
    void changeTitle(const State& state);
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
