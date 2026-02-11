#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include "solve.cpp"

using namespace std;

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
