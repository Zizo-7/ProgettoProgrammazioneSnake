#pragma once
#include <ncurses.h>
#include <iostream>

class Input
{
private:
    char nomeGiocatore[20];
    int livello;

public:
    Input();
    void inserisci_nome();
    void seleziona_livello();
    int getLivello() const;
    std::string getNome() const { return std::string(nomeGiocatore); }
};