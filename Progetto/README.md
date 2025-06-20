# ProgettoProgrammazioneSnake

Progetto di programmazione snake utilizzando la libreria ncurses
Descrizione
Questo progetto è un semplice gioco di Snake realizzato in C utilizzando la libreria ncurses. Il gioco permette di controllare un serpente che si muove su uno schermo, cercando di mangiare cibo per guadagnare punti. Il gioco termina quando il serpente collide con se stesso, oppure quando il timer scade, oppure quando il giocatore decide di uscire.

## caratteristiche del gioco

- **Movimenti serpente**:Il serpente si muove in una direzione e può essere controllato con i tasti freccia.
- **Livelli**: Il gioco ha cinque livelli di difficoltà, che influenzano la velocità del serpente e il valore del cibo.
- **Timer**: Il gioco ha un timer che scade dopo 60 secondi, al termine del quale il gioco termina.
- **Punteggio**: Il punteggio viene calcolato in base al numero di cibi mangiati e al livello di difficoltà. -**Bonus**: al completamento di ogni livello, vengono aggiunti bonus al punteggio. Maggiore è il livello, maggiore è il bonus.
- **Nomi giocatori**: Il gioco permette di inserire il nome del giocatore all'inizio del gioco.
- **Salvataggio punteggio**: Il punteggio finale viene salvato in un file di testo, che può essere visualizzato in seguito. -**tabella punteggi**: Il gioco permette di visualizzare la tabella dei punteggi, che mostra i punteggi dei giocatori e i loro nomi.
- **Game Over**: Il gioco termina quando il serpente collide con se stesso, oppure quando il timer scade, oppure quando il giocatore decide di uscire.

## Requisiti

- **g++ Compiler**: Compilatore per compilare il progetto

- **Libreria ncurses**: Utilizzata per la grafica del gioco. Può essere installata con il gestore di pacchetti del sistema operativo:
  -Debian: `sudo apt-get install libncurses5-dev libncursesw5-dev`

## Compilazione e Avvio

1. compilare il progetto con il comando:

   ```bash
   make
   ```

   2. Avviare il gioco:

   ```bash
   ./game

   ```
