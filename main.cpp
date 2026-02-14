#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <math.h>
#include <algorithm>

using namespace std;


bool checkPossible (short r, short c, short n);
void print ();

short N;
short l;
vector<vector<short>> grid;

class Point {
    private:
        short row;
        short column;
        pair<short, short> cell0;
        set<short> options;
    public:
        Point () {}
        Point (short row, short column) : row(row), column(column) {
            cell0.first = (row/l) * l;
            cell0.second = (column/l) * l;
            options.clear();
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
        void printOptions () {
            for (short n : options) {
                cout << n << " ";
            }
            cout << endl;
        }
        const set<short> getOptions () const {
            return options;
        }
        void setValue (short n);


        bool operator <(const Point& b) const {
            return this->getOptions().size() < b.getOptions().size();
        }
};

vector<vector<Point*>> points;

struct BetterPrecision {
    bool operator ()(const Point* a, const Point* b) const {
        return a->getOptions().size() < b->getOptions().size();
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

bool solveDLX (priority_queue<Point*, vector<Point*>, BetterPrecision> comb);


int main () {
    // setup griglia
    cin >> N;
    l = sqrt(N);
    grid.resize(N);
    points.resize(N);
    for (short i=0; i<N; i++) {
        grid[i].resize(N);
        points[i].resize(N);
    }
    
    // input sudoku
    for (short i=0; i<N; i++) {
        for (short j=0; j<N; j++) 
            cin >> grid[i][j];
    }
    cout << endl;

    priority_queue<Point*, vector<Point*>, BetterPrecision> comb;

    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            points[i][j]->initOptions();
            comb.emplace(points[i][j]);
        }
    }

    // solveDLX (comb);
    
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



void print () {
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) 
            cout << grid[i][j] << ((j+1)%(int)sqrt(N) == 0 ? "  " : " ");
        cout << ((i+1)%(int)sqrt(N) == 0 ? "\n" : "") << endl;
    }
    cout << endl << endl;
}


void Point::setValue (short n)  {
    grid[this->row][this->column] = n;
    for (int i=0; i<N; i++) {
        points[this->row][i]->removeOption(n);
        points[i][this->column]->removeOption(n);
    }
    for (int i=this->cell0.first; i<this->cell0.first+l; i++) {
        for (int j=this->cell0.second; j<this->cell0.second+l; j++)
        points[i][j]->removeOption(n);
    }
}

// return:
//   0 se corretto
//   1 se errore
bool solveDLX (priority_queue<Point*, vector<Point*>, BetterPrecision> comb) {
    // controllo esistenza elementi
    if (comb.size() == 0) return 0;

    // primo elemento della lista -> meno possibilità
    Point P = *comb.top();

    // non ha possibilità
    if (P.getOptions().size() == 0) return 1;

    // ha 1 possibilità
    if (P.check_possible(*P.getOptions().begin())) {
        P.setValue(*P.getOptions().begin());
        comb.pop();
        return 0;
    } else return 1;

    // ha più possibilità
    
}