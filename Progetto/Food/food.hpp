#ifndef FOOD_H
#define FOOD_H

#include "../Snake/snake.hpp" // Per usare Position

class Food
{
public:
    Position pos;

    Food();
    void generate();
    void draw(WINDOW *win) const;
};

#endif
