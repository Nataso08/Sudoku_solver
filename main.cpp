#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

bool check (const int size, const vector<vector<int>>& sudoku) {
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

void print_sudoku (const int size, const vector<vector<int>>& sudoku) {
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
    
    int solved_cells = 0;
    
    bool go_back = false;
    
    pair<int, int> cell = {0, 0};
    
    while (solved_cells < empty_cells) {
        system("cls");
        print_sudoku(size, sudoku);
        
        // find empty cell
        while (sudoku[cell.first][cell.second] != 0 && !go_back) {
            cell.second ++;
            if (cell.second >= size) {
                cell.first ++;
                cell.second = 0;
            }

            if (cell.first >= size && cell.second >= size) break;
        }
        
        // increment value of finded cell as long as sudoku is ok or value of this cell is larger than size (max value)
        do {
            sudoku[cell.first][cell.second] ++;

            if (sudoku[cell.first][cell.second] > size) break;
        } while (!check(size, sudoku));
        
        // "overflow" of this cell
        if (sudoku[cell.first][cell.second] > size) {
            sudoku[cell.first][cell.second] = 0;
            
            // find last editable cell
            do {
                cell.second --;
                if (cell.second < 0) {
                    cell.first --;
                    cell.second = size -1;
                }
                
                if (cell.first < 0 || cell.second < 0) break;
                
                if (sudoku_input[cell.first][cell.second] == 0) solved_cells --;
            } while (sudoku_input[cell.first][cell.second] != 0);
            
            go_back = true;
        } else {
            if (sudoku_input[cell.first][cell.second] == 0) solved_cells ++;
            go_back = false;
        }
    }
    


    print_sudoku (size, sudoku);

    // return 0;
}