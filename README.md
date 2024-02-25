# project-tetris
1)Mattia/paim : tetramini casuali (iniziale + successivo) ( 4x1, 2x2 + eventuali), movimento, caduta, rotazione, collisioni, scelta tetramini, inserimento giocatore 
2) riccardo/biagio: finestra, menu (nuova partita, classifica decresc in un altro file (punteggio, nome giocatore)), rimozione righe + aggiunta punti

### Lista tetramini:
Composto da un array bidimensionale, il .h "tetramini" contiene sette tipi di tetramini con 4 possibili rotazioni ognuno rappresentate da una matrice 4x4 di valori interi.

### Classe Tetramino:
La classe "Tetramino" si occupa dei principali movimenti dei tetramini all'interno della tavola di gioco:  
+ la funzione "aggiorna tavola" si occupa di aggiornare la tavola di gioco con la posizione corrente del tetramino, prendendo in considerazione la sua posizione (x, y) e la sua rotazione. Viene eseguito un controllo per assicurarsi di non accedere a elementi al di fuori delle dimensioni del tetramino, e i valori vengono copiati nella tavola di gioco.
+ la funzione "collisioni bordo" si occupa di controllare se uno dei blocchi del tetramino sia trova al di fuori della tavola di gioco, indicando una collisione che viene utilizzata nelle funzioni di movimento.
+ le funzioni di movimento permettono lo spostamento del tetramino solo se non avvengono collisioni con il bordo.
+ la funzione "ruota" si occupa di ruotare il tetramino per poi verificare che non siano avvenute collisioni con il bordo, in caso affermativo annulla la rotazione.
