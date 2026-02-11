#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

bool check (int size, const vector<vector<int>>& sudoku) {
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
            if (sudoku[row][column] != 0) {
                c[sudoku[row][column] -1] ++;
    
                if (c[sudoku[row][column] -1] > 1) return false;
            }
        }
    }

    // grids control
    int grid_size = sqrt(size);

    vector<vector<vector<int>>> grid (grid_size, vector<vector<int>> (grid_size, vector<int> (size, 0)));

    for (int row=0; row<size; row++) {
        for (int column=0; column<size; column++) {
            if (sudoku[row][column] != 0) {
                grid[row/grid_size][column/grid_size][sudoku[row][column] -1] ++;
    
                if (grid[row/grid_size][column/grid_size][sudoku[row][column] -1] > 1) return false;
            }
        }
    }

    return true;
}

bool check (int size, const vector<vector<int>>& sudoku, const pair<int, int>& cell) {
    int x = sudoku[cell.first][cell.second];
    
    for (int i=0; i<size; i++) {
        if (sudoku[cell.first][i] == x && i != cell.second || sudoku[i][cell.second] == x && i != cell.first) return false;
    }

    int box_size = sqrt(size);

    pair<int, int> limit_row = {
        (cell.first/box_size) * box_size, 
        (cell.first/box_size + 1) * box_size
    };
    pair<int, int> limit_column = {
        ((int) cell.second/box_size) * box_size, 
        ((int) cell.second/box_size + 1) * box_size
    };

    for (int row=limit_row.first; row<limit_row.second; row++) {
        for (int column=limit_column.first; column<limit_column.second; column++) {
            if (sudoku[row][column] == x && !(row == cell.first && column == cell.second)) return false;
        }
    }

    return true;
}
