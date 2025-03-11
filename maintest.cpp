#include <iostream>
#include <ncurses.h>
#include <cstring>
#include "Menu/Menu.hpp"

int main()
{
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    cbreak();

    Menu menu;
    menu.visualizza_menu();

    getch();
    endwin();
    return 0;
}