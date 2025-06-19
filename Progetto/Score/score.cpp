#include "score.hpp"

// costruttore
Score::Score()
{
    // Inizializza la finestra della classifica
    int maxHeigth, maxWidth;
    getmaxyx(stdscr, maxHeigth, maxWidth);
    this->score_win = newwin(maxHeigth, maxWidth, 0, 0);

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
void Score::resetScoreWindow()
{
    // Resetta la finestra della classifica
    werase(this->score_win);
    wrefresh(this->score_win);

    refresh();
}

void Score::dispalyScoreWindow(const std::string &filename)
{
    wclear(this->score_win);
    // box(this->menuwin, 0, 0);

    std::ifstream file(filename);
    if (!file.is_open())
    {
        mvwprintw(this->score_win, 1, 1, "Error opening file");
        wrefresh(this->score_win);
        return;
    }

    box(this->score_win, 0, 0);

    int width = getmaxx(this->score_win);
    int hight = getmaxy(this->score_win);

    std::string line;
    mvwprintw(this->score_win, 3, (width / 2) - 5, "SCORE TABLE");
    mvwprintw(this->score_win, (hight - 13), (width / 2) - 9, "click 'b' to go back");
    int row = 1;
    while (std::getline(file, line))
    {
        mvwprintw(this->score_win, row + 7, (width / 2) - 4, line.c_str());
        row += 3;
    }
    file.close();
    wrefresh(this->score_win);
}

int Score::bonusInBaseAlLivello(int livello)
{
    // Restituisce il bonus in base al livello
    switch (livello)
    {
    case 1:
        return 0;
    case 2:
        return 3;
    case 3:
        return 6;
    case 4:
        return 9;
    case 5:
        return 12;
    default:
        return 0; // Livello non valido, nessun bonus
    }
}