#include "Menu.hpp"

Menu::Menu()
{
}

void Menu::visualizza_menu()
{
    Menu::visualizza_grafica();
    mvprintw(35, 5, "Premi il tasto 's' per iniziare il gioco");
    mvprintw(38, 5, "Premi il tasto 'q' per uscire");
    mvprintw(41, 5, "Premi il tasto 't' per visualizzare i punteggi");
    refresh();
}

void Menu::visualizza_grafica()
{
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    int rows = SPRINT_ROWS;
    int cols = strlen(sprite[0]); // Misura la larghezza dello sprite

    // Ottieni dimensioni della finestra
    int height, width;
    getmaxyx(stdscr, height, width);
    // Calcola posizione centrale per il titolo
    int starty = (10 - rows) / 2;
    int startx = (width - cols) / 2;

    // Stampa il titolo dello sprite
    attron(COLOR_PAIR(1));
    for (int i = 0; i < rows; ++i)
    {
        mvprintw(starty + i, startx, "%s", sprite[i]);
    }
    attroff(COLOR_PAIR(1));

    // Calcola posizione centrale per il serpente
    int snakeStartY = starty + rows + 1; // Posizione sotto il titolo
    int snakeStartX = (width - strlen(snake[0])) / 2;

    // Stampa il serpente
    for (int i = 0; i < SNAKE_ROWS; ++i)
    {
        mvprintw(snakeStartY + i, snakeStartX, "%s", snake[i]);
    }
}