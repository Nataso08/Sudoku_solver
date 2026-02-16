#include "solve.h"


// dimensioni del Sudoku
short N = 9;    // Lato
short l = 3;    // Lato sottogriglia

vector<vector<short>> Sudoku;
vector<vector<Cell>> cells;

Cell unused (-1, -1);

// Inizio classe Cell

// COSTRUTTORI

// Costruttore
Cell::Cell() {}
/*
Costruttore
#### Parametri:
- row -> index riga della cella
- column -> index colonna della cella
*/
Cell::Cell(short row, short column) {
    this->setPos(row, column);
    this->options.clear();
}

// GESTIONE POSIZIONE

/*
Setting posizione
#### Parametri:
- row -> index riga della cella
- column -> index colonna della cella
*/
void Cell::setPos (short row, short column) {
    this->row = row;
    this->column = column;
    
    cell0.first = (row/l) * l;
    cell0.second = (column/l) * l;
}

/*
Restituzione posizione
#### Restituisce:
Pair {row, column} relativi alla cella
*/
const pair<short, short> Cell::getPos () const {
    return {this->row, this->column};
}

/*
Restituzione posizione
#### Restituisce:
- Pair {row, column} relativi alla cella origine della sottogriglia (alto sinistra)
*/
const pair<short, short> Cell::getCell0 () const {
    return cell0;
}


// VERIFICA POSSIBILITÀ

/*
Verifica possibilità
#### Parametri:
- n -> valore da verificare
*/
bool Cell::checkPossible (short n) {
    for (int i=0; i<N; i++) {
        if (Sudoku[this->row][i] == n) return 0;
        if (Sudoku[i][this->column] == n) return 0;
    }
    for (int i=cell0.first; i<cell0.first+l; i++) 
        for (int j=cell0.second; j<cell0.second+l; j++) 
            if (Sudoku[i][j] == n) return 0;
    
    return 1;
}

// GESTIONE OPZIONI

/*
Inizializzazione delle opzioni
*/
void Cell::initOptions () {
    for (short n=1; n<=N; n++) 
        this->addOption(n);
}
/*
Rimozione di un'opzione
#### Parametri:
- n -> valore da rimuovere
*/
void Cell::removeOption (short n) {
    if (Sudoku[this->row][this->column] == 0) options.erase(n);
}

/*
Aggiunta di un'opzione
#### Parametri:
- n -> valore da aggiungere (se possibile)
*/
void Cell::addOption (short n) {
    if (Sudoku[this->row][this->column] != 0) return ;
    if (checkPossible(n)) options.insert(n);
}

/*
Restituzione opzioni
#### Restituisce:
- set contenente le opzioni accettabili relative alla cella
*/
const set<short> Cell::getOptions () const {
    return options;
}

// IMPOSTAZIONE VALORE

/*
Impostazione valore
#### Parametri:
- n -> numero da impostare
*/
void Cell::setValue (short n)  {
        // this->removeOption(n);
    Sudoku[this->row][this->column] = n;
    for (int i=0; i<N; i++) {
        cells[this->row][i].removeOption(n);
        cells[i][this->column].removeOption(n);
    }
    for (int i=this->cell0.first; i<this->cell0.first+l; i++) {
        for (int j=this->cell0.second; j<this->cell0.second+l; j++)
            cells[i][j].removeOption(n);
    }
    options.erase(n);
    return ;
}

/*
Impostazione valore. Imposta il primo valore delle opzioni, togliendolo dal set
*/
void Cell::setValueFirst () {
    this->setValue(*(this->options.begin()));
}

// RESET CELLA

/*
Reset della cella. Ripristina 0 nel sudoku, re-inizializza le opzioni
*/
void Cell::reset () {
    Sudoku[this->row][this->column] = 0;
    initOptions();
}

// Fine classe Cell


// Funzione solve


/*
Funzione di risoluzione
#### Restituisce:
- 0 -> risoluzione avvenuta con successo
- 1 -> errore nella risoluzione
*/
bool solve () {
    // individuazione punto con meno combinazioni
    Cell* bestPoint = findBestCell();

    // non ci sono celle vuote
    if (bestPoint == &unused) return 0;

    // 1 o più combinazioni possibili
    while (bestPoint->getOptions().size() > 0) {
        bestPoint->setValueFirst();
        if (!solve()) return 0;
        short n = Sudoku[bestPoint->getPos().first][bestPoint->getPos().second];
        Sudoku[bestPoint->getPos().first][bestPoint->getPos().second] = 0;
        restoreX(*bestPoint, n);
        bestPoint->removeOption(n);
    }
    
    // non riuscito a risolvere
    bestPoint->reset();
    return 1;
}


// FUNZIONI RESTORE_X

/*
Ripristino opzioni ad X. Aggiunge (verificando) tutte le opzioni
#### Parametri:
- P -> cella origine del cambiamento 
*/
void restoreX (const Cell& P) {
    for (short n=1; n<=N; n++) restoreX(P, n);
}
/*
Ripristino opzioni ad X. Aggiunge (verificando) n
#### Parametri:
- P -> cella origine del cambiamento 
- n -> valore da aggiungere
*/
void restoreX (const Cell& P, short n) {
    const pair<short, short> pos = P.getPos();
    const pair<short, short> cell0 = P.getCell0();

    for (int i=0; i<N; i++) {
        cells[pos.first][i].addOption(n);
        cells[i][pos.second].addOption(n);
    }
    for (int i=cell0.first; i<cell0.first+l; i++) {
        for (int j=cell0.second; j<cell0.second+l; j++) 
            cells[i][j].addOption(n);
    }
    return ;
}


// FUNZIONE FIND_BEST_CELL

/*
Individua la cella con meno opzioni possibili.
#### Restituisce:
- puntatore alla cella con meno opzioni
*/
Cell* findBestCell () {
    Cell* bestPoint = &unused;
    short bestSize = N;

    for (short i=0; i<N; i++) {
        for (short j=0; j<N; j++) {
            if (Sudoku[i][j] == 0) {
                if (cells[i][j].getOptions().size() <= 1) return &(cells[i][j]);
                if (cells[i][j].getOptions().size() < bestSize) {
                    bestSize = cells[i][j].getOptions().size();
                    bestPoint = &(cells[i][j]);
                }
            }
        }
    }
    
    return bestPoint;
}


// FUNZIONE PRINT

/*
Stampa il Sudoku sulla console
*/
void print () {
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) 
            cout << Sudoku[i][j] << ((j+1)%(int)sqrt(N) == 0 ? "  " : " ");
        cout << ((i+1)%(int)sqrt(N) == 0 ? "\n" : "") << endl;
    }
    cout << endl << endl;
}
/*
Stampa il Sudoku su file
*/
void print (ofstream& fout) {
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) 
            fout << Sudoku[i][j] << ((j+1)%(int)sqrt(N) == 0 ? "  " : " ");
        fout << ((i+1)%(int)sqrt(N) == 0 ? "\n" : "") << endl;
    }
    fout << endl << endl;
}
