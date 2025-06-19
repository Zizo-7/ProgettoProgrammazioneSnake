#ifndef GAME_H
#define GAME_H
#pragma once

#include "Snake/snake.hpp"
#include "Food/food.hpp"
#include "Menu/Menu.hpp"
#include "Score/score.hpp"
#include "Input/Input.hpp"
#include "Timer/timer.hpp"
#include "constants.hpp"
#include <ncurses.h>
#include <iostream>
#include <cstring>
#include <time.h>
#include <ctime>
#include <cstdlib>

class Game
{
private:
    Menu menu;
    Snake snake;
    Food food;
    Score scoreManager;
    int score = 0;
    int delay = 100;
    int moveDelay;
    int livello;
    StatoGioco currentState;
    std::string playerName;
    WINDOW *board_win;

public:
    Game(int livello, std::string nome);
    ~Game();
    void run();
    void mainMenu();
    void scoreTableMenu();
    void gameLoop();
    void deleteBoardWin();
    void speedDelay();
};

#endif
