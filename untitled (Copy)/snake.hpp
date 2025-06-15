#ifndef SNAKE_H
#define SNAKE_H

#include <ncurses.h>

const int WIDTH = 40;
const int HEIGHT = 20;
const int INITIAL_LENGTH = 9;

struct Position {
    int x, y;
};

class Snake {
private:
    bool grid[HEIGHT][WIDTH] = {false};
    void updateHeadSymbol();

public:
    Position body[WIDTH * HEIGHT];
    int length;
    int dx, dy;
    char head_symbol;

    Snake();
    bool move(const Position& food_pos);
    void draw(WINDOW* win) const;
    void changeDirection(int ch);
};

#endif
