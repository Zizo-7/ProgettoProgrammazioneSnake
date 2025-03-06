#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

const int WIDTH = 40;
const int HEIGHT = 20;
const int INITIAL_LENGTH = 6;

typedef struct {
    int x, y;
} Position;

void generate_food(Position *food) {
    food->x = rand() % (WIDTH - 2) + 1;
    food->y = rand() % (HEIGHT - 2) + 1;
}

int main() {
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    timeout(100);

    WINDOW *board_win = newwin(HEIGHT, WIDTH, 0, 0);
    box(board_win, 0, 0);
    wrefresh(board_win);

    Position snake[WIDTH * HEIGHT];
    int length = INITIAL_LENGTH;

    for (int i = 0; i < length; i++) {
        snake[i].x = WIDTH / 2 - i;
        snake[i].y = HEIGHT / 2;
    }

    Position food;
    generate_food(&food);
    int score = 0;
    int dx = 1, dy = 0;

    while (1) {
        werase(board_win);
        box(board_win, 0, 0);

        mvwprintw(board_win, food.y, food.x, "@");

        for (int i = 0; i < length; i++) {
            mvwprintw(board_win, snake[i].y, snake[i].x, "O");
        }

        mvprintw(HEIGHT, 0, "Score: %d", score);

        wrefresh(board_win);
        refresh();

        int ch = getch();
        if (ch == 'q') break;
        if (ch == KEY_UP && dy == 0) { dx = 0; dy = -1; }
        if (ch == KEY_DOWN && dy == 0) { dx = 0; dy = 1; }
        if (ch == KEY_LEFT && dx == 0) { dx = -1; dy = 0; }
        if (ch == KEY_RIGHT && dx == 0) { dx = 1; dy = 0; }

        Position new_head = {snake[0].x + dx, snake[0].y + dy};

        if (new_head.x < 1) new_head.x = WIDTH - 2;
        if (new_head.x >= WIDTH - 1) new_head.x = 1;
        if (new_head.y < 1) new_head.y = HEIGHT - 2;
        if (new_head.y >= HEIGHT - 1) new_head.y = 1;

        for (int i = 0; i < length; i++) {
            if (snake[i].x == new_head.x && snake[i].y == new_head.y) {
                endwin();
                printf("Game Over! Final Score: %d\n", score);
                return 0;
            }
        }

        for (int i = length - 1; i > 0; i--) {
            snake[i] = snake[i - 1];
        }
        snake[0] = new_head;

        if (new_head.x == food.x && new_head.y == food.y) {
            score++;
            generate_food(&food);
        }
    }

    endwin();
    return 0;
}
