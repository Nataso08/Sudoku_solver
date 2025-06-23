#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
struct column_control {
    int column;
    int n;

    column_control(int column, int n) : column(column), n(n) {}

    bool operator() () {

    }
};
*/


bool valid (int size, vector<vector<short>> sudoku) {
    // rows control
    for (int row=0; row<size; row++) {
        for (int i=1; i<=size; i++) {
            if (count(sudoku[row].begin(), sudoku[row].end(), i) > 1) return false;
        }
    }

    // columns control
    for (int column=0; column<size; column++) {
        vector<int> c (size, 0);
        for (int row=0; row<size; row++) {
            c[sudoku[row][column] -1] ++;
            if (c[sudoku[row][column] -1] > 1) return false;
        }
    }

    // grids control
        
}

int main () {
    int size;
    cout << "Insert the sudoku dimension: >>> ";
    cin >> size;

    vector<vector<short>> sudoku_input, sudoku;

    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            cin >> sudoku_input[i][j];
        }
    }




    return 0;
}