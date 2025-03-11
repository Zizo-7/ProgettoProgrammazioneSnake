#pragma once
#include <ncurses.h>
#include <iostream>
#include <cstring>
#define Start 's'
#define Quit 'q'

enum StatoGioco
{
    MENU,
    GIOCO,
    TABELLA_PUNTEGGI,
    ESCI
};

extern const char *sprite[];
extern const char *snake[];

extern const int SPRINT_ROWS;
extern const int SNAKE_ROWS;