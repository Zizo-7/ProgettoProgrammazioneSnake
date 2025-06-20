
#include "game.hpp"
struct LivelloNode
{
    int livello;
    int moveDelay;
    LivelloNode *prev;
    LivelloNode *next;
};

Game::Game(int livello = 1, std::string nome = "Player")
{

    srand(time(NULL));
    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    this->score = 0;
    scoreManager.readScoreFromFileAndSaveInScoreTable("scoretable.txt");
    this->livello = livello;
    this->playerName = nome;
    this->currentState = MENU;
}

Game::~Game()
{
    endwin();
}

void Game::run()
{
    while (true)
    {
        switch (currentState)
        {
        case MENU:
            mainMenu();
            break;
        case GIOCO:
            gameLoop();
            break;
        case TABELLA_PUNTEGGI:
            scoreTableMenu();
            break;
        case ESCI:
            return; // Esce dal gioco
        default:
            break;
        }
    }
}

void Game::mainMenu()
{
    menu.visualizza_menu();
    int ch = getch();
    if (ch == 's')
    {
        this->currentState = GIOCO;
    }
    else if (ch == 't')
    {
        this->currentState = TABELLA_PUNTEGGI;
    }
    else if (ch == 'q')
    {
        this->currentState = ESCI;
    }
}
void Game::scoreTableMenu()
{
    menu.reset_menuWindow();
    scoreManager.dispalyScoreWindow("scoretable.txt");
    refresh();
    int ch = wgetch(scoreManager.score_win);
    if (ch == 'b')
    {
        scoreManager.resetScoreWindow();
        this->currentState = MENU;
    }
}

void Game::gameLoop()
{
    menu.reset_menuWindow();
    Input input;
    input.inserisci_nome();
    this->playerName = input.getNome();

    input.seleziona_livello();
    this->livello = input.getLivello();
    speedDelay(); // Imposta il delay in base al livello

    int frutta_valore = this->livello;
    bool isGameOver = false;
    refresh();
    getch();
    this->board_win = newwin(HEIGHT, WIDTH, 15, 100);
    box(board_win, 0, 0);
    wrefresh(this->board_win);

    timeout(moveDelay); // molto reattivo
    int tick = 0;

    Timer timer(1); // Crea un timer di 3 minuti
    timer.start();  // Avvia il timer

    while (this->currentState == GIOCO && !isGameOver)
    {

        timer.draw(); // Disegna il timer a schermo alla posizione (0, 0)
        int ch = getch();
        if (ch == 'q')
        {
            scoreManager.addScore((char *)playerName.c_str(), this->score);
            scoreManager.saveScoreInFile();
            scoreManager.readScoreFromFileAndSaveInScoreTable("scoretable.txt");
            scoreManager.SortScoretable();
            this->score = 0; // Resetta il punteggio
            timer.undraw();  // Resetta il timer
            deleteBoardWin();
            this->currentState = MENU;
            isGameOver = true;
        }

        if (ch == KEY_UP && snake.dy == 0)
        {
            snake.dx = 0;
            snake.dy = -1;
        }
        if (ch == KEY_DOWN && snake.dy == 0)
        {
            snake.dx = 0;
            snake.dy = 1;
        }
        if (ch == KEY_LEFT && snake.dx == 0)
        {
            snake.dx = -1;
            snake.dy = 0;
        }
        if (ch == KEY_RIGHT && snake.dx == 0)
        {
            snake.dx = 1;
            snake.dy = 0;
        }

        if (tick % moveDelay == 0)
        {
            bool growing = snake.move(food.pos);

            if (snake.hasCollidedWithSelf())
            {
                scoreManager.addScore((char *)playerName.c_str(), this->score);
                scoreManager.saveScoreInFile();
                scoreManager.readScoreFromFileAndSaveInScoreTable("scoretable.txt");
                scoreManager.SortScoretable();
                this->score = 0; // Resetta il punteggio

                timer.undraw(); // Resetta il timer
                deleteBoardWin();
                this->currentState = MENU;
                isGameOver = true;
            }

            if (growing)
            {
                food.generate();
                score = score + frutta_valore;
            }

            werase(board_win);
            box(board_win, 0, 0);
            food.draw(board_win);
            snake.draw(board_win);
            mvprintw(13, 100, "Score: %d", score);
            wrefresh(board_win);
            refresh();
        }

        if (timer.isExpired())
        {
            this->score += scoreManager.bonusInBaseAlLivello(this->livello);
            scoreManager.addScore((char *)playerName.c_str(), this->score);
            scoreManager.saveScoreInFile();
            scoreManager.readScoreFromFileAndSaveInScoreTable("scoretable.txt");
            scoreManager.SortScoretable();
            this->score = 0; // Resetta il punteggio
            timer.undraw();  // Resetta il timer
            deleteBoardWin();
            this->currentState = MENU;
            isGameOver = true;
        }

        tick++;
    }
}
void Game::deleteBoardWin()
{
    werase(board_win);
    wrefresh(board_win);
    delwin(board_win);
    board_win = nullptr;
    refresh();
}
void Game::speedDelay()
{
    // Inizializza la lista dei livelli
    LivelloNode livello1 = {1, 12, nullptr, nullptr};
    LivelloNode livello2 = {2, 10, &livello1, nullptr};
    LivelloNode livello3 = {3, 8, &livello2, nullptr};
    LivelloNode livello4 = {4, 6, &livello3, nullptr};
    LivelloNode livello5 = {5, 4, &livello4, nullptr};
    livello1.next = &livello2;
    livello2.next = &livello3;
    livello3.next = &livello4;
    livello4.next = &livello5;

    // Trova il nodo corrispondente al livello richiesto
    LivelloNode *ptr = &livello1;
    while (ptr != nullptr && ptr->livello != this->livello)
    {
        ptr = ptr->next;
    }
    if (ptr != nullptr)
    {
        this->moveDelay = ptr->moveDelay;
    }
    else
    {
        this->moveDelay = 10; // valore di default
    }
}
