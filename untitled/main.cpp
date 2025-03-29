#include <ncurses.h>
#include <stdlib.h>
#include <cstring>
#include <time.h>
using namespace std;

const int WIDTH = 40;
const int HEIGHT = 20;
const int INITIAL_LENGTH = 6;

struct Position {
    int x, y;
};

class Food {
public:
    Position pos;

    Food() { generate(); }

    void generate() {
        pos.x = rand() % (WIDTH - 2) + 1;
        pos.y = rand() % (HEIGHT - 2) + 1;
    }

    void draw(WINDOW *win) {
        mvwprintw(win, pos.y, pos.x, "@");
    }
};

class Snake {
public:
    Position body[WIDTH * HEIGHT];
    bool grid[HEIGHT][WIDTH] = {false};
    int length;
    int dx, dy;
    char head_symbol;

    Snake() {
        dx = 1; dy = 0;
        length = INITIAL_LENGTH;
        for (int i = 0; i < length; i++) {
            body[i] = { WIDTH / 2 - i, HEIGHT / 2 };
            grid[body[i].y][body[i].x] = true;
        }
        updateHeadSymbol();
    }

    void updateHeadSymbol() {
        if (dx == 1) head_symbol = '>';
        else if (dx == -1) head_symbol = '<';
        else if (dy == 1) head_symbol = 'v';
        else if (dy == -1) head_symbol = '^';
    }

    bool move(Position food_pos) {
        Position new_head = { body[0].x + dx, body[0].y + dy };

        if (new_head.x < 1) new_head.x = WIDTH - 2;
        if (new_head.x >= WIDTH - 1) new_head.x = 1;
        if (new_head.y < 1) new_head.y = HEIGHT - 2;
        if (new_head.y >= HEIGHT - 1) new_head.y = 1;

        if (grid[new_head.y][new_head.x]) {
            return false; // Collisione con se stesso
        }

        Position tail = body[length - 1];
        grid[tail.y][tail.x] = false; // Rimuove la coda

        for (int i = length - 1; i > 0; i--) {
            body[i] = body[i - 1];
        }
        body[0] = new_head;
        grid[new_head.y][new_head.x] = true; // Aggiorna la nuova testa

        if (new_head.x == food_pos.x && new_head.y == food_pos.y) {
            return true;
        }

        updateHeadSymbol();
        return false;
    }

    void draw(WINDOW *win) {
        mvwprintw(win, body[0].y, body[0].x, "%c", head_symbol);
        for (int i = 1; i < length; i++) {
            mvwprintw(win, body[i].y, body[i].x, "O");
        }
    }
};

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    timeout(100);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    // Sprite: un cuore stilizzato
    const char* sprite[] = {
        "      ___           ___           ___           ___           ___                    ___           ___           ___           ___     ",
        "     /\\  \\         /\\__\\         /\\  \\         /\\__\\         /\\  \\                  /\\  \\         /\\  \\         /\\__\\         /\\  \\    ",
        "    /::\\  \\       /::|  |       /::\\  \\       /:/  /        /::\\  \\                /::\\  \\       /::\\  \\       /::|  |       /::\\  \\   ",
        "   /:/\\ \\  \\     /:|:|  |      /:/\\:\\  \\     /:/__/        /:/\\:\\  \\              /:/\\:\\  \\     /:/\\:\\  \\     /:|:|  |      /:/\\:\\  \\  ",
        "  _\\:\\~\\ \\  \\   /:/|:|  |__   /::\\~\\:\\  \\   /::\\__\\____   /::\\~\\:\\  \\            /:/  \\:\\  \\   /::\\~\\:\\  \\   /:/|:|__|__   /::\\~\\:\\  \\ ",
        " /\\ \\:\\ \\ \\__\\ /:/ |:| /\\__\\ /:/\\:\\ \\:\\__\\ /:/\\:::::\\__\\ /:/\\:\\ \\:\\__\\          /:/__/\\_\\:\\__\\ /:/\\:\\ \\:\\__\\ /:/ |::::\\__\\ /:/\\:\\ \\:\\__\\",
        " \\:\\ \\:\\ \\/__/ \\/__|:|/:/  / \\/__\\/:\\/:/  / \\/_|:|~~|~    \\:\\~\\:\\ \\/__/          \\:\\  /\\ \\/__/ \\/__\\/:\\/:/  / \\/__/~~/:/  / \\:\\~\\:\\ \\/__/ ",
        "  \\:\\ \\:\\__\\       |:/:/  /       \\::/  /     |:|  |      \\:\\ \\:\\__\\             \\:\\ \\:\\__\\        \\::/  /        /:/  /   \\:\\ \\:\\__\\  ",
        "   \\:\\/:/  /       |::/  /        /:/  /      |:|  |       \\:\\ \\/__/              \\:\\/:/  /        /:/  /        /:/  /     \\:\\ \\/__/  ",
        "    \\::/  /        /:/  /        /:/  /       |:|  |        \\:\\__\\                 \\::/  /        /:/  /        /:/  /       \\:\\__\\    ",
        "     \\/__/         \\/__/         \\/__/         \\|__|         \\/__/                  \\/__/         \\/__/         \\/__/         \\/__/    "
    };

    // Sprite: il serpente
    const char* snake_sprite[] = {
        "           /^\\/^\\                                           ",
        "         _|__|  O|                                          ",
        " \\/     /~     \\_/ \\                                        ",
        "  \\____|__________/  \\                                      ",
        "         \\_______      \\                                    ",
        "                 `\\     \\                 \\                 ",
        "                   |     |                  \\                ",
        "                  /      /                    \\               ",
        "                 /     /                       \\\\             ",
        "               /      /                         \\ \\            ",
        "              /     /                            \\  \\           ",
        "            /     /             _----_            \\   \\         ",
        "           /     /           _-~      ~-_         |   |        ",
        "          (      (        _-~    _--_    ~-_     _/   |        ",
        "           \\      ~-____-~    _-~    ~-_    ~-_-~    /         ",
        "             ~-_           _-~          ~-_       _-~         ",
        "                ~--______-~                ~-___-~              "
    };

    int rows = sizeof(sprite) / sizeof(sprite[0]);
    int cols = strlen(sprite[0]); // Misura la larghezza dello sprite

    // Ottieni dimensioni della finestra
    int height, width;
    getmaxyx(stdscr, height, width);

    // Calcola posizione centrale per il titolo
    int starty = (10 - rows) / 2;
    int startx = (width - cols) / 2;

    // Stampa il titolo dello sprite
    attron(COLOR_PAIR(1));
    for (int i = 0; i < rows; ++i) {
        mvprintw(starty + i, startx, "%s", sprite[i]);
    }
    attroff(COLOR_PAIR(1));

    // Calcola posizione centrale per il serpente
    int snakeStartY = starty + rows + 1; // Posizione sotto il titolo
    int snakeStartX = (width - strlen(snake_sprite[0])) / 2;

    // Stampa il serpente
    for (int i = 0; i < sizeof(snake_sprite) / sizeof(snake_sprite[0]); ++i) {
        mvprintw(snakeStartY + i, snakeStartX, "%s", snake_sprite[i]);
    }


    while (getch() != 'q') {

    }
     clear();

    srand(time(NULL));

    WINDOW *board_win = newwin(HEIGHT, WIDTH, 15, 100);
    box(board_win, 0, 0);
    wrefresh(board_win);

    Snake snake;
    Food food;
    int score = 0;

    while (true) {
        werase(board_win);
        box(board_win, 0, 0);

        food.draw(board_win);
        snake.draw(board_win);

        mvprintw(HEIGHT, 0, "Score: %d", score);
        wrefresh(board_win);
        refresh();

        int ch = getch();
        if (ch == 'q') break;
        if (ch == KEY_UP && snake.dy == 0) { snake.dx = 0; snake.dy = -1; }
        if (ch == KEY_DOWN && snake.dy == 0) { snake.dx = 0; snake.dy = 1; }
        if (ch == KEY_LEFT && snake.dx == 0) { snake.dx = -1; snake.dy = 0; }
        if (ch == KEY_RIGHT && snake.dx == 0) { snake.dx = 1; snake.dy = 0; }

        if (snake.move(food.pos)) {
            food.generate();
            score++;
        }
    }

    endwin();
    return 0;
}
