#include <iostream>
#include <ncurses.h>
#include <cstring>
#include "Menu/Menu.hpp"
#include "Input/Input.hpp"

int main()
{
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    cbreak();

    // visualizzare il menu principale
    Menu menu;
    menu.visualizza_menu();
    getch();

    wclear(stdscr);
    refresh();
    // chiedere nome e livello
    Input input;
    input.inserisci_nome();
    input.seleziona_livello();

    getch();

    endwin();
    return 0;
}