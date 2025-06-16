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

    char mario[] = "Mario";
    char luigi[] = "Luigi";
    char peach[] = "Peach";

    score.addScore(mario, 100);
    score.addScore(luigi, 200);
    score.addScore(peach, 150);

    score.saveScoreInFile();

    score.readScoreFromFileAndSaveInScoreTable("scoretable.txt");
    score.SortScoretable();

    cout << score.scoretablearray[9].score << "-------";
    getch();

    endwin();
    return 0;
}