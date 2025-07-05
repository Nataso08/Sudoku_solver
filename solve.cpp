#include <vector>
#include <algorithm>
#include <math.h>
#include "func.cpp"
#include "check.cpp"

using namespace std;

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