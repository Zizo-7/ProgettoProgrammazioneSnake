#include "snake.hpp"

Snake::Snake()
{
    dx = 1;
    dy = 0;
    length = INITIAL_LENGTH;
    for (int i = 0; i < length; ++i)
    {
        body[i] = {WIDTH / 2 - i, HEIGHT / 2};
        grid[body[i].y][body[i].x] = true;
    }
    updateHeadSymbol();
}

void Snake::updateHeadSymbol()
{
    if (dx == 1)
        head_symbol = '>';
    else if (dx == -1)
        head_symbol = '<';
    else if (dy == 1)
        head_symbol = 'v';
    else if (dy == -1)
        head_symbol = '^';
}

bool Snake::move(const Position &food_pos)
{
    Position new_head = {body[0].x + dx, body[0].y + dy};

    if (new_head.x < 1)
        new_head.x = WIDTH - 2;
    if (new_head.x >= WIDTH - 1)
        new_head.x = 1;
    if (new_head.y < 1)
        new_head.y = HEIGHT - 2;
    if (new_head.y >= HEIGHT - 1)
        new_head.y = 1;

    if (grid[new_head.y][new_head.x])
        return false;

    Position tail = body[length - 1];
    grid[tail.y][tail.x] = false;

    for (int i = length - 1; i > 0; --i)
        body[i] = body[i - 1];

    body[0] = new_head;
    grid[new_head.y][new_head.x] = true;
    updateHeadSymbol();

    if (new_head.x == food_pos.x && new_head.y == food_pos.y)
    {
        // length++;
        return true;
    }
    return false;
}

void Snake::draw(WINDOW *win) const
{
    mvwprintw(win, body[0].y, body[0].x, "%c", head_symbol);
    for (int i = 1; i < length; ++i)
        mvwprintw(win, body[i].y, body[i].x, "O");
}

void Snake::changeDirection(int ch)
{
    if (ch == KEY_UP && dy == 0)
    {
        dx = 0;
        dy = -1;
    }
    else if (ch == KEY_DOWN && dy == 0)
    {
        dx = 0;
        dy = 1;
    }
    else if (ch == KEY_LEFT && dx == 0)
    {
        dx = -1;
        dy = 0;
    }
    else if (ch == KEY_RIGHT && dx == 0)
    {
        dx = 1;
        dy = 0;
    }
}
