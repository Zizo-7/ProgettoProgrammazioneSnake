#pragma once
#include <ncurses.h>
#include <iostream>

class Input
{
protected:
    char nomeGiocatore[20];
    int livello;

public:
    Input();
    void inserisci_nome();
    void seleziona_livello();
};