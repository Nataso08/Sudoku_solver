#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

void print_sudoku (int size, const vector<vector<int>>& sudoku) {
    cout << endl;

    int grid_size = sqrt(size);

    for (int row=0; row<size; row++) {
        if (row % grid_size == 0) {
            for (int i=0; i<(size+grid_size)*2 +1; i++) {
                cout << '-';
            }
            cout << endl;
        }
        for (int column=0; column<size; column++) {
            if (column % grid_size == 0) cout << "| ";
            cout << sudoku[row][column] << " ";
        }
        cout << '|';
        cout << endl;
    }

    for (int i=0; i<(size+grid_size)*2 +1; i++) {
        cout << '-';
    }
    cout << endl;
}
