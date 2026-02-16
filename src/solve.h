#ifndef SOLVE_H
#define SOLVE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <math.h>

using namespace std;


// Classe Cell:
class Cell {
    private:
        // Posizione
        short row;
        short column;
        pair<short, short> cell0;
        // Opzioni
        set<short> options;
    public:
        // Costruttori
        Cell ();
        Cell (short row, short column);

        // Gesione posizone
        void setPos (short row, short column);
        const pair<short, short> getPos () const;
        const pair<short, short> getCell0 () const;
        // Controllo possibilità
        bool checkPossible (short n);
        // Gestione opzioni
        void initOptions ();
        void removeOption (short n);
        void addOption (short n);
        const set<short> getOptions () const ;
        // Impostazione valore
        void setValue (short n);
        void setValueFirst ();
        // Reset cella
        void reset ();
};


// Soluzione
bool solve ();

// Ripristino ad X (re-inserimento opzioni)
void restoreX (const Cell& P);
void restoreX (const Cell& P, short n);

// Individuazione cella migliore
Cell* findBestCell ();

// Stampa Sudoku
void print ();
void print (ofstream& fout);



// dimensioni del Sudoku
extern short N;    // Lato
extern short l;    // Lato sottogriglia


extern vector<vector<short>> Sudoku;
extern vector<vector<Cell>> cells;




#endif