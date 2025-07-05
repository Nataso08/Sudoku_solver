# Sudoku_solver
A sudoku solver (at the moment only standard type, but with any dimension) completely made ourself in C++ using brute-force solution method (but in order to setting up a better solve method, using standard rules too).

## Steps
- input size
- input sudoku
- checking solvability
- while sudoku is not solved
    - try standard rules solve
    - if is not possible to complete the sudoku with this rules, use brute force solving method
- print solved sudoku