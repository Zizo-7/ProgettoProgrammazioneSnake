#ifndef GAME_H
#define GAME_H
#pragma once

#include "Snake/snake.hpp"
#include "Food/food.hpp"
#include "Menu/Menu.hpp"
#include "Score/score.hpp"
#include "Input/Input.hpp"
#include "constants.hpp"
#include <ncurses.h>
#include <iostream>
#include <cstring>

class Game
{
private:
    Snake snake;
    Food food;
    int score = 0;
    int delay = 100;
    int moveDelay;
    WINDOW *board_win;

public:
    Game(int livello);
    ~Game();
    void run();
};

#endif
