#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

short N;
vector<vector<short>> grid;

struct findColumn {
    short c;
    short n;

    findColumn (short c, short n) : c(c), n(n) {}

    bool operator ()(const vector<short>& row) const {
        return row[c] == n;
    }
};

bool checkPossible (short r, short c, short n);
void solve (int i0, int j0);
void print ();


int main () {
    // setup griglia
    cin >> N;
    grid.resize(N);
    for (short i=0; i<N; i++) grid[i].resize(N);
    
    // input sudoku
    for (short i=0; i<N; i++) {
        for (short j=0; j<N; j++) 
            cin >> grid[i][j];
    }
    cout << endl;

    solve(0, 0);

    print();
}



bool checkPossible (short r, short c, short n) {
    // 1) check row
    if (find(grid[r].begin(), grid[r].end(), n) != grid[r].end()) return 0;


    // 2) check column
    if (find_if(grid.begin(), grid.end(), findColumn(c, n)) != grid.end()) return 0;


    // 3) check square
    short l = sqrt(N);
    
    // cella origine quadrato
    short r0 = (r/l) *l;
    short c0 = (c/l) *l;

    for (int i=r0; i<r0+l; i++) {
        for (int j=c0; j<c0+l; j++) 
            if (grid[i][j] == n) return 0;
    }

    return 1;
}

void solve (int i0, int j0) {
    print();
    for (int i=i0; i<N; i++) {
        for (int j=j0; j<N; j++) {
            if (grid[i][j] == 0) {
                for (int n=1; n<=N; n++) {
                    if (checkPossible(i, j, n)) {
                        grid[i][j] = n;
                        solve (0, 0);
                        grid[i][j] = 0;
                        print();
                    }
                }
                return ;
            }
        }
    }
}

void print () {
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) 
            cout << grid[i][j] << ((j+1)%(int)sqrt(N) == 0 ? "  " : " ");
        cout << ((i+1)%(int)sqrt(N) == 0 ? "\n" : "") << endl;
    }
    cout << endl << endl;
}
