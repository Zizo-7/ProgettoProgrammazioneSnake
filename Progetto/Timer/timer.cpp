#include "timer.hpp"
#include <ncurses.h>
#include <sstream>
#include <iostream>

Timer::Timer(int minutes) // Costruttore: imposta la durata del timer in secondi (default: 3 minuti)
{
    durationSeconds = minutes * 60;
    startTime = 0;
    boxwin = nullptr; // Inizializza la finestra a nullptr
}

// Avvia il timer salvando il tempo corrente
void Timer::start()
{
    startTime = time(nullptr); // time(nullptr) restituisce il tempo attuale in secondi (UNIX time)
}

// Calcola quanti secondi mancano alla scadenza del timer
int Timer::getRemainingSeconds() const
{
    time_t now = time(nullptr);                      // tempo attuale in secondi
    int elapsed = static_cast<int>(now - startTime); // Calcola il tempo trascorso in secondi
    int remaining = durationSeconds - elapsed;       // Calcola i secondi rimanenti
    if (remaining > 0)
        return remaining;
    else
        return 0; // Se il tempo rimanente è negativo, restituisce 0
}

// Ritorna true se il tempo è scaduto
bool Timer::isExpired() const
{
    return getRemainingSeconds() <= 0;
}
// Disegna il timer a schermo alla posizione (y, x)
void Timer::draw() const
{

    // Crea una finestra 4 righe x 20 colonne
    WINDOW *boxwin = newwin(4, 20, 0, 0);
    box(boxwin, 0, 0); // Disegna la cornice

    int remaining = getRemainingSeconds();
    int minutes = remaining / 60;
    int seconds = remaining % 60;
    // Formatta il tempo come MM:SS
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "Timer: %02d:%02d", minutes, seconds);
    mvprintw(0, 0, "%s", buffer);
}

void Timer::undraw()
{
    if (boxwin != nullptr)
    {
        delwin(boxwin);   // Elimina la finestra del timer
        boxwin = nullptr; // Imposta a nullptr per evitare doppie eliminazioni
    }
    clear();   // Pulisce lo schermo
    refresh(); // Aggiorna lo schermo
}