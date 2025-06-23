#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

bool check (int size, vector<vector<int>> sudoku) {
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
    int grid_size = sqrt(size);

    vector<vector<vector<int>>> grid (grid_size, vector<vector<int>> (grid_size, vector<int> (size, 0)));

    for (int row=0; row<size; row++) {
        for (int column=0; column<size; column++) {
            grid[row/grid_size][column/grid_size][sudoku[row][column] -1] ++;

            if (grid[row/grid_size][column/grid_size][sudoku[row][column] -1] > 1) return false;
        }
    }

    return true;
}

void print_sudoku (int size, vector<vector<int>> sudoku) {
    cout << endl;

    for (int row=0; row<size; row++) {
        for (int column=0; column<size; column++) {
            cout << sudoku[row][column] << " ";
        }
        cout << endl;
    }
}

int main () {
    int size;
    cout << "Insert the sudoku dimension: >>> ";
    cin >> size;

    vector<vector<int>> sudoku_input (size, vector<int> (size, 0));

    int empty_cells = 0;

    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            cin >> sudoku_input[i][j];

            if (sudoku_input[i][j] == 0) empty_cells ++;
        }
    }

    if (!check(size, sudoku_input)) {
        cout << "The inserted sudoku is unsolvable" << endl;
        return 0;
    }

    vector<vector<int>> sudoku = sudoku_input;

    int tried_cells = 0;

    pair<int, int> last_cell = {0, 0};

    /*do {






    } while (!check(size, sudoku) || tried_cells < empty_cells);

    */


    print_sudoku (size, sudoku);

    return 0;
}