#pragma once
#include <ncurses.h>
#include <iostream>
#include <cstring>
#include "../constants.hpp"
#pragma once
#include <ctime>

class Timer
{
private:
    time_t startTime;
    int durationSeconds;
    WINDOW *boxwin; // Finestra per il timer

public:
    Timer(int minutes = 3); // Default: 3 minuti
    void start();
    int getRemainingSeconds() const; // Ritorna quanti secondi mancano alla fine

    // const indica che questa funzione non modifica l'oggetto
    bool isExpired() const;
    void draw() const; // stampa il timer a posizione (y, x)
    void undraw();     // Resetta il timer
};
