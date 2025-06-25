#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

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

int regular_solve (int size, vector<vector<int>>& sudoku, int empty_cells) {
    int change = 0;

    do {
        for (int row=0; row<size; row++) {
            for (int column=0; column<size; column++) {
                if (sudoku[row][column] == 0) {
                    int c = 0, s;

                    for (int x=1; x<=size; x++) {
                        sudoku[row][column] = x;

                        if (check(size, sudoku, {row, column})) {
                            if (++c > 1) break;
                            s = x;
                        }
                    }

                    if (c == 1) {
                        sudoku[row][column] = s;
                        empty_cells --;
                        change ++;
        
                        system("cls");
                        print_sudoku(size, sudoku);
                    } else if (c == 0) {
                        return -1;
                    } else {
                        sudoku[row][column] = 0;
                    }
                }
            }
        }
    } while (empty_cells > 0 && change > 0);

    return empty_cells;
}

void brute_force_solve (int size, vector<vector<int>>& sudoku, int empty_cells) {
    vector<pair<int, int>> cells (0);
    for (int row = 0; row<size; row ++) {
        for (int column = 0; column<size; column ++) {
            if (sudoku[row][column] == 0) cells.emplace_back(row, column);
        }
    }

    int x=0;
    pair<int, int> cell = cells[0];
    bool go_back = false;

    do {
        while (sudoku[cell.first][cell.second] != 0 && x != cells.size() -1 && !go_back) {
            cell = cells[++ x];
        }

        do {
            sudoku[cell.first][cell.second] ++;
        } while (!check(size, sudoku, cell) && sudoku[cell.first][cell.second] <= size);

        if (sudoku[cell.first][cell.second] > size) {
            do {
                empty_cells ++;
                sudoku[cell.first][cell.second] = 0;
                if (x > 0) cell = cells[-- x];
                else break;
                if (sudoku[cell.first][cell.second] < size) {
                    sudoku[cell.first][cell.second] ++;
                    break;
                }
            } while (sudoku[cell.first][cell.second] >= size);
            go_back = true;
        } else {
            empty_cells --;
            go_back = false;
        }
    } while (empty_cells > 0);
}

/*
void solve (int size, vector<vector<int>>& sudoku, int empty_cells) {
    
    do {
        
    } while (empty_cells);
}
*/


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

    // regular_solve (size, sudoku_input, empty_cells);
    
    vector<vector<int>> sudoku = sudoku_input;
    
    int solved_cells = 0;

    brute_force_solve(size, sudoku, empty_cells);

    system("cls");
    // cout << regular_solve (size, sudoku, empty_cells) << endl;
    // print_sudoku(size, sudoku);

    print_sudoku (size, sudoku);

    system("pause");

    return 0;
}