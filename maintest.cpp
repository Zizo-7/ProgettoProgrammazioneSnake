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
    // cbreak();
    nodelay(stdscr, TRUE);

    /*
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
    wclear(stdscr);
    refresh();

    Game game;
    game.run();
*/

    // Crea e avvia il timer (3 minuti di default)
    Timer timer;   // Crea timer di 3 minuti
    timer.start(); // Avvia il timer

    while (!timer.isExpired())
    {
        clear();          // Pulisce schermo
        timer.draw(0, 0); // Mostra timer
        mvprintw(2, 0, "Premi 'q' per uscire.");
        refresh(); // Aggiorna ncurses

        int ch = getch(); // Legge input non bloccante
        if (ch == 'q')
            break; // Esce se premi 'q'

        napms(100); // Attendi 100ms (≈10 FPS)
    }

    clear();
    mvprintw(5, 5, "Tempo scaduto!");
    mvprintw(7, 5, "Premi un tasto per uscire.");
    refresh();

    nodelay(stdscr, FALSE); // Rimetti getch() in modalità bloccante
    getch();                // Attendi tasto
    endwin();               // Chiudi ncurses
    return 0;
}