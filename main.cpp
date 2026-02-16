#include <iostream>
#include "src/solve.h"

using namespace std;

int main () {
    // setup griglia
    cout << "Inserire la dimensione del Sudoku: >>> ";
    cin >> N;
    l = sqrt(N);
    Sudoku.resize(N);
    cells.resize(N);
    cout << "Inserisci il Sudoku: " << endl;
    for (short i=0; i<N; i++) {
        Sudoku[i].resize(N);
        cells[i].resize(N);
    }
    
    // input sudoku
    for (short i=0; i<N; i++) {
        for (short j=0; j<N; j++) 
            cin >> Sudoku[i][j];
    }
    cout << endl;

    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            cells[i][j].setPos(i, j);
            if (Sudoku[i][j] == 0) {
                cells[i][j].initOptions();
            }
        }
    }

    solve();

    cout << "Solved: " << endl;
    print();
}

