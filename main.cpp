#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <math.h>
#include <algorithm>

using namespace std;


bool checkPossible (short r, short c, short n);
pair<short, short> findEmpty ();
bool solve ();
void print ();

bool solveDLX (priority_queue<Point, vector<Point>, BetterPrecision>  comb);


short N;
short l;
vector<vector<short>> grid;

class Point {
    private:
        short row;
        short column;
        set<short> options;
    public:
        Point () {}
        Point (short row, short column) : row(row), column(column) {
            options.clear();
        }
        void setPos (short row, short column) {
            this->row = row;
            this->column = column;
        }
        bool check_possible (short n) {
            return checkPossible(this->row, this->column, n);
        }
        void initOptions () {
            for (short n=1; n<=N; n++) {
                if (check_possible(n)) options.insert(n);
            }
        }
        void removeOption (short n) {
            options.erase(n);
        }
        void updateOptions () {
            for (short n : options) {
                if (!check_possible(n)) removeOption (n);
            }
        }
        void printOptions () {
            for (short n : options) {
                cout << n << " ";
            }
            cout << endl;
        }
        set<short> getOptions () {
            return options;
        }
        void setValue (short n) {
            grid[this->row][this->column] = n;
            for (int i=0; i<N; i++) {
                
            }
        }
};


struct findColumn {
    short c;
    short n;

    findColumn (short c, short n) : c(c), n(n) {}

    bool operator ()(const vector<short>& row) const {
        return row[c] == n;
    }
};

struct BetterPrecision {
    bool operator ()(Point& a, Point& b) const {
        return a.getOptions().size() < b.getOptions().size();
    }
};

int main () {
    // setup griglia
    cin >> N;
    grid.resize(N);
    l = sqrt(N);
    for (short i=0; i<N; i++) grid[i].resize(N);
    
    // input sudoku
    for (short i=0; i<N; i++) {
        for (short j=0; j<N; j++) 
            cin >> grid[i][j];
    }
    cout << endl;

    // test Point su grid
    Point a (0, 0);
    a.initOptions ();
    a.printOptions ();
    // grid[0][1] = 4;
    a.updateOptions ();
    a.printOptions ();

    priority_queue<Point, vector<Point>, BetterPrecision>  comb;
    
    solveDLX (comb);
    
    // solve();

    cout << "Solved: " << endl;
    print();
}



bool checkPossible (short r, short c, short n) {
    // 1) check row
    if (find(grid[r].begin(), grid[r].end(), n) != grid[r].end()) return 0;


    // 2) check column
    if (find_if(grid.begin(), grid.end(), findColumn(c, n)) != grid.end()) return 0;


    // 3) check square
    // cella origine quadrato
    short r0 = (r/l) *l;
    short c0 = (c/l) *l;

    for (int i=r0; i<r0+l; i++) {
        for (int j=c0; j<c0+l; j++) 
            if (grid[i][j] == n) return 0;
    }

    return 1;
}

pair<short, short> findEmpty () {
    for (short i=0; i<N; i++) {
        for (short j=0; j<N; j++) {
            if (grid[i][j] == 0) return (pair<short, short>) {i, j};
        }
    }

    return (pair<short, short>) {-1, -1};
}

bool solve () {
    // print();
    pair<short, short> RC = findEmpty ();

    if (RC.first == -1) return 1;

    for (int n=1; n<=N; n++) {
        if (checkPossible(RC.first, RC.second, n)) {
            grid[RC.first][RC.second] = n;
            if (solve ()) break;
            grid[RC.first][RC.second] = 0;
            // print();
        } 
        if (n == N) return 0;
    }

    return 1;
}
bool solveDLX (priority_queue<Point, vector<Point>, BetterPrecision>  comb) {
    if (comb.size() == 0) return 1;
    if (comb.size() == 1) {
        Point P = comb.top();
        if (P.check_possible(*(P.getOptions().end()))) {

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
