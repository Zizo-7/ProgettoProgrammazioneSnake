#include "score.hpp"

// costruttore
Score::Score()
{
    // Inizializza l'array di punteggi a zero
    for (int i = 0; i < 10; i++)
    {
        this->scoretablearray[i].score = 0;
        strcpy(this->scoretablearray[i].nome, " ");
    }
}
void Score::SortScoretable()
{
    // Ordinamento dei punteggi in ordine decrescente
    for (int i = 0; i < 10; i++)
    {
        for (int j = i + 1; j < 10; j++)
        {
            if (scoretablearray[i].score < this->scoretablearray[j].score)
            {
                Scoretable temp = scoretablearray[i];
                scoretablearray[i] = scoretablearray[j];
                scoretablearray[j] = temp;
            }
        }
    }
}
void Score::readScoreFromFileAndSaveInScoreTable(const std::string &filename)
{
    // Legge i punteggi da un file e li salva nella struttura
    std::ifstream file(filename);
    if (file.is_open())
    {
        for (int i = 0; i < 10; i++)
        {
            file >> this->scoretablearray[i].nome;
            file >> scoretablearray[i].score;
        }
        file.close();
    }
}
void Score::saveScoreInFile()
{
    this->SortScoretable(); // Ordina i punteggi prima di salvarli
    // Salva i punteggi in un file
    std::ofstream file("scoretable.txt");
    if (file.is_open())
    {
        for (int i = 0; i < 10; i++)
        {
            file << this->scoretablearray[i].nome << " " << this->scoretablearray[i].score << std::endl;
        }
        file.close();
    }
}
// Funzione per aggiungere un punteggio alla classifica e se l'array è pieno e il punteggio è maggiore del punteggio più basso, lo sostituisce
void Score::addScore(char name[], int punteggio)
{
    // Aggiunge un punteggio alla classifica senza usare scorecount
    bool aggiunto = false;
    int i = 0;
    while (i < 10 && aggiunto == false)
    {
        if (this->scoretablearray[i].score == 0)
        {
            strcpy(this->scoretablearray[i].nome, name);
            this->scoretablearray[i].score = punteggio;
            aggiunto = true;
        }
        i++;
    }
    SortScoretable(); // Ordina i punteggi dopo aver aggiunto il nuovo punteggio
    if (aggiunto == false)
    {
        if (punteggio > this->scoretablearray[9].score)
        {
            strcpy(this->scoretablearray[9].nome, name);
            this->scoretablearray[9].score = punteggio;
        }
    }
    SortScoretable(); // Ordina i punteggi dopo aver aggiunto il nuovo punteggio
}
// Funzione per visualizzare la classifica
void Score::visualizzaClassifica()
{
    // Visualizza la classifica dei punteggi
    clear();
    mvprintw(0, 0, "Classifica:");
    for (int i = 0; i < 10; i++)
    {
        mvprintw(i + 1, 0, "%d. %s - %d", i + 1, this->scoretablearray[i].nome, this->scoretablearray[i].score);
    }
    refresh();
}