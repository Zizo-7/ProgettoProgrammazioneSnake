#include <iostream>
#include <ncurses.h>
#include <cstring>
#include "Score/score.hpp"
using namespace std;

int main()
{
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    cbreak();

    Score score;

    char mario[] = "Marioo";
    char luigi[] = "Luigi";
    char peach[] = "Peach";
    char toad[] = "Toad";
    char yoshi[] = "Yoshi";
    char bowser[] = "Bowser";

    score.addScore(mario, 100);
    score.addScore(luigi, 200);
    score.addScore(peach, 150);
    score.addScore(toad, 300);
    score.addScore(yoshi, 250);
    score.addScore(bowser, 400);

    score.saveScoreInFile();

    score.readScoreFromFileAndSaveInScoreTable("scoretable.txt");
    score.SortScoretable();
    score.visualizzaClassifica();

    getch(); // Attende un tasto prima di chiudere
    endwin();
    return 0;
}