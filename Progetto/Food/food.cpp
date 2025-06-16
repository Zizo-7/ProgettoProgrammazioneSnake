#include "food.hpp"
#include <stdlib.h>

Food::Food() {
    generate();
}

void Food::generate() {
    pos.x = rand() % (WIDTH - 2) + 1;
    pos.y = rand() % (HEIGHT - 2) + 1;
}

void Food::draw(WINDOW* win) const {
    mvwprintw(win, pos.y, pos.x, "@");
}
