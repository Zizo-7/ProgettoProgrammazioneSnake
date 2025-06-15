#pragma once
#include <cstring>
#include <iostream>  // std::cout, std::endl
#include <string>    // std::string
#include <fstream>   // lettura/scrittura file
#include <ncurses.h> // gestione grafica ncurses

// Struttura per contenere il nome e punteggio
struct Scoretable
{
    char nome[20]; // Nome del giocatore
    int score;     // Punteggio
};

// Classe Score che gestisce la classifica
class Score
{
private:
    char nomegiocatore[20]; // Nome del giocatore

public:
    Scoretable scoretablearray[10];
    Score(); // Costruttore
    // Array di strutture per i punteggi
    void SortScoretable();                                                  // Funzione per ordinare i punteggi
    void readScoreFromFileAndSaveInScoreTable(const std::string &filename); // Funzione per leggere i punteggi da un file e salvarli nella struttura
    void saveScoreInFile();
    void addScore(char name[], int punteggio); // Funzione per salvare i punteggi nell'array
};

// sort()ordina, legge dal file e salva nella struttura ,  saveScoreInFile(); ho nome e score e salvo nella mia struct,
//