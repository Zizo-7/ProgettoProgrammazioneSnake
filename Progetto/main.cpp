#include <iostream>
#include <ncurses.h>
#include <cstring>
#include "game.hpp"
#include "Menu/Menu.hpp"
#include "Input/Input.hpp"
#include "Timer/timer.hpp"

int main()
{
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    cbreak();

    Game game(1, "Player"); // Inizializza il gioco con livello 1 e nome "Player"
    game.run();             // Avvia il gioco
}