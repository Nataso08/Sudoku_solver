#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <math.h>
#include <algorithm>

using namespace std;

bool checkPossible (short r, short c, short n);
void print ();

short N = 9;
short l = 3;
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
        void setPos (short row, short column) {
            this->row = row;
            this->column = column;
            
            cell0.first = (row/l) * l;
            cell0.second = (column/l) * l;
        }
        const pair<short, short> getPos () const {
            return {this->row, this->column};
        }
        const pair<short, short> getCell0 () const {
            return cell0;
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
            if (grid[this->row][this->column] == 0) options.erase(n);
        }
        void addOption (short n) {
            if (grid[this->row][this->column] != 0) return ;
            if (check_possible(n)) options.insert(n);
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
        void setValueFirst () {
            this->setValue(*(this->options.begin()));
        }
        void reset () {
            grid[this->row][this->column] = 0;
            initOptions();
        }

        bool operator <(const Point& b) const {
            return this->getOptions().size() < b.getOptions().size();
        }
};

vector<vector<Point>> points;
Point buffer (-1, -1);

struct BestPrecision {
    bool operator ()(const Point* a, const Point* b) const {
        return a->getOptions().size() > b->getOptions().size();
    }
};

Point* findBestCell ();

struct findColumn {
    short c;
    short n;

    findColumn (short c, short n) : c(c), n(n) {}

    bool operator ()(const vector<short>& row) const {
        return row[c] == n;
    }
};

void updateX (const Point& P, short n);
void updateX (const Point& P);
bool solve ();

int main () {
    // debug
    ifstream cin ("test.txt");

    // setup griglia
    cout << "Inserire la dimensione del Sudoku: >>> ";
    cin >> N;
    l = sqrt(N);
    grid.resize(N);
    points.resize(N);
    cout << "Inserisci il Sudoku: " << endl;
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

    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            points[i][j].setPos(i, j);
            if (grid[i][j] == 0) {
                points[i][j].initOptions();
            }
        }
    }

    // debug
    /*
    Point* a = comb.top();
    cout << a << endl;
    
    for (short n : a->getOptions()) cout << n << " ";
    cout << endl;
    a->removeOption(4);
    for (short n : a->getOptions()) cout << n << " ";
    cout << endl << endl;
    */

    solve();

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
    this->removeOption(n);
    grid[this->row][this->column] = n;
    for (int i=0; i<N; i++) {
        points[this->row][i].removeOption(n);
        points[i][this->column].removeOption(n);
    }
    for (int i=this->cell0.first; i<this->cell0.first+l; i++) {
        for (int j=this->cell0.second; j<this->cell0.second+l; j++)
            points[i][j].removeOption(n);
    }
    return ;
}

Point* findBestCell () {
    Point* bestPoint = &buffer;
    short bestSize = N;

    for (short i=0; i<N; i++) {
        for (short j=0; j<N; j++) {
            if (grid[i][j] == 0) {
                if (points[i][j].getOptions().size() == 1) return &(points[i][j]);
                if (points[i][j].getOptions().size() < bestSize) {
                    bestSize = points[i][j].getOptions().size();
                    bestPoint = &(points[i][j]);
                }
            }
        }
    }
    
    return bestPoint;
}
void updateX (const Point& P, short n) {
    const pair<short, short> pos = P.getPos();
    const pair<short, short> cell0 = P.getCell0();

    for (int i=0; i<N; i++) {
        points[pos.first][i].addOption(n);
        points[i][pos.second].addOption(n);
    }
    for (int i=cell0.first; i<cell0.first+l; i++) {
        for (int j=cell0.second; j<cell0.second+l; j++) 
            points[i][j].addOption(n);
    }
}
void updateX (const Point& P) {
    for (short n=1; n<=N; n++) updateX(P, n);
}

// return:
//   0 se corretto
//   1 se errore
bool solve () {
    // individuazione punto con meno combinazioni
    Point* bestPoint = findBestCell();

    // non ci sono celle vuote
    if (bestPoint == &buffer) return 0;

    // 1 sola combinazione possibile:
    if (bestPoint->getOptions().size() == 1) {
        bestPoint->setValueFirst();
        if (solve()) {
            updateX(*bestPoint, grid[bestPoint->getPos().first][bestPoint->getPos().second]);
            bestPoint->reset();
            return 1;
        }
        return 0;
    }

    // più opzioni possibili:
    while (bestPoint->getOptions().size() > 0) {
        bestPoint->setValueFirst();
        if (!solve()) return 0;
        updateX(*bestPoint, grid[bestPoint->getPos().first][bestPoint->getPos().second]);
        grid[bestPoint->getPos().first][bestPoint->getPos().second] = 0;
    }
    
    // non riuscito a risolvere
    bestPoint->reset();
    return 1;
}
