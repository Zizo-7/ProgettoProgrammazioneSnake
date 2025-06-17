#include "Input.hpp"
#

Input::Input()
{
}

void Input::inserisci_nome()
{
    echo();
    WINDOW *inputwin = newwin(3, 40, 22, 64);
    box(inputwin, 0, 0);
    mvwprintw(inputwin, 1, 1, "Enter your name: ");
    wrefresh(inputwin);
    wgetnstr(inputwin, this->nomeGiocatore, 20);
    wrefresh(inputwin);
    delwin(inputwin);
    noecho();
}

void Input::seleziona_livello()
{

    int maxY = getmaxy(stdscr);
    int maxX = getmaxx(stdscr);

    WINDOW *inputwin = newwin(3, 40, 22, 64);
    box(inputwin, 0, 0);
    mvwprintw(inputwin, 1, 1, "Select Level: from 1 to 5");
    wrefresh(inputwin);
    this->livello = getch() - '0';
    wrefresh(inputwin);
    delwin(inputwin);
}
int Input::getLivello() const
{
    return this->livello;
}