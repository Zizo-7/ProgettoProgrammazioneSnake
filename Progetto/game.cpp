
#include "game.hpp"

void Game::showGameOverMenu()
{
    clear();
    mvprintw(10, 40, "GAME OVER");
    mvprintw(12, 40, "Score: %d", score);
    mvprintw(14, 40, "Premi S per ricominciare");
    mvprintw(15, 40, "Premi T per vedere la classifica");
    mvprintw(16, 40, "Premi Q per uscire");
    refresh();

    Score scoreManager;
    scoreManager.readScoreFromFileAndSaveInScoreTable("scoretable.txt");
    scoreManager.addScore((char *)playerName.c_str(), score);
    scoreManager.saveScoreInFile();

    int ch;
    while (true)
    {
        ch = getch();
        if (ch == 's' || ch == 'S')
        {
            Input input;
            input.inserisci_nome();
            input.seleziona_livello();
            Game newGame(input.getLivello(), input.getNome());
            newGame.run();
            break;
        }
        else if (ch == 't' || ch == 'T')
        {
            scoreManager.visualizzaClassifica();
            mvprintw(20, 40, "Premi un tasto per tornare al menu...");
            refresh();
            getch();
            showGameOverMenu();
            break;
        }
        else if (ch == 'q' || ch == 'Q')
        {
            break;
        }
    }
}

Game::Game(int livello, std::string nome)
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

    board_win = newwin(HEIGHT, WIDTH, 15, 100);
    box(board_win, 0, 0);
    wrefresh(board_win);

    switch (livello)
    {
    case 1:
        moveDelay = 10; // lento
        break;
    case 2:
        moveDelay = 8; // normale
        break;
    case 3:
        moveDelay = 6; // veloce
        break;
    case 4:
        moveDelay = 4; // rapidissima
        break;
    case 5:
        moveDelay = 2; // massima
        break;
    default:
        moveDelay = 10; // default normale
        break;
    }
}

Game::~Game()
{
    endwin();
}

void Game::run()
{

    timeout(10); // molto reattivo
    int tick = 0;
    // più basso = più veloce
    /*come ho fatto, la funzione timeout(10) -> ogni 10 ms fa un esecuzione, se timeout è 100 allora è troppo lento
     * mentre se timeout è 10 ci sono troppi cicli e quindi a prescindere risulta lento
     * usiamo un metodo con tick e move delay, dove tick conta i cicli, e ogni tot cicli (in base a move delay) verrà avviato un ciclo
     * non usando questo modo, il codice va fuori controllo e risulta più lento di prima
     * 12: lento, 8 normale, 4 veloce, 2 rapidissima, 1 massima
     */
    Timer timer(1); // Crea un timer di 3 minuti
    timer.start();  // Avvia il timer

    while (true)
    {
        timer.draw(0, 0); // Disegna il timer a schermo alla posizione (0, 0)
        int ch = getch();
        if (ch == 'q')
            break;
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

            if (snake.hasCollidedWithSelf()) // hasCollidedWithSelf() NON FUNZIONA CORRETTAMENTE
            {
                showGameOverMenu();
                break;
            }

            if (growing)
            {
                food.generate();
                score++;
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
            showGameOverMenu();
            break;
        }

        tick++;
    }
}

/*void Game::showGameOverMenu()
{
    clear();
    mvprintw(10, 40, "GAME OVER");
    mvprintw(12, 40, "Score: %d", score);
    mvprintw(14, 40, "Premi S per ricominciare");
    mvprintw(15, 40, "Premi T per vedere la classifica");
    mvprintw(16, 40, "Premi Q per uscire");
    refresh();

    Score scoreManager;
    scoreManager.readScoreFromFileAndSaveInScoreTable("scoretable.txt");
    scoreManager.addScore((char *)playerName.c_str(), score);
    scoreManager.saveScoreInFile();

    int ch;
    while (true)
    {
        ch = getch();
        if (ch == 's' || ch == 'S')
        {
            Input input;
            input.inserisci_nome();
            input.seleziona_livello();
            Game newGame(input.livello, input.getNome());
            newGame.run();
            break;
        }
        else if (ch == 't' || ch == 'T')
        {
            scoreManager.visualizzaClassifica();
            mvprintw(20, 40, "Premi un tasto per tornare al menu...");
            refresh();
            getch();
            showGameOverMenu();
            break;
        }
        else if (ch == 'q' || ch == 'Q')
        {
            break;
        }
    }
}

Game::Game(int livello)
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

    board_win = newwin(HEIGHT, WIDTH, 15, 100);
    box(board_win, 0, 0);
    wrefresh(board_win);

    switch (livello)
    {
    case 1:
        moveDelay = 10; // lento
        break;
    case 2:
        moveDelay = 8; // normale
        break;
    case 3:
        moveDelay = 6; // veloce
        break;
    case 4:
        moveDelay = 4; // rapidissima
        break;
    case 5:
        moveDelay = 2; // massima
        break;
    default:
        moveDelay = 10; // default normale
        break;
    }
}
*/
/*Game::~Game()
{
    endwin();
}

/*void Game::run()
{

    timeout(10); // molto reattivo
    int tick = 0;
    // più basso = più veloce
    /*come ho fatto, la funzione timeout(10) -> ogni 10 ms fa un esecuzione, se timeout è 100 allora è troppo lento
     * mentre se timeout è 10 ci sono troppi cicli e quindi a prescindere risulta lento
     * usiamo un metodo con tick e move delay, dove tick conta i cicli, e ogni tot cicli (in base a move delay) verrà avviato un ciclo
     * non usando questo modo, il codice va fuori controllo e risulta più lento di prima
     * 12: lento, 8 normale, 4 veloce, 2 rapidissima, 1 massima
     */

/* while (true)
 {
     int ch = getch();
     if (ch == 'q')
         break;
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
         if (snake.move(food.pos))
         {
             food.generate();

             score++;
         }

         werase(board_win);
         box(board_win, 0, 0);
         food.draw(board_win);
         snake.draw(board_win);
         mvprintw(13, 100, "Score: %d", score);
         wrefresh(board_win);
         refresh();
     }

     tick++;
 }
}*/