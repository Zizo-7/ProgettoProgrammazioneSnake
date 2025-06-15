#ifndef GAME_H
#define GAME_H

#include "snake.hpp"
#include "food.hpp"

class Game {
private:
    Snake snake;
    Food food;
    int score = 0;
    int delay = 100;
    WINDOW* board_win;

public:
    Game();
    ~Game();
    void run();
};

#endif
