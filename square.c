#include "sudoku.h"

int solve_square(Square *square) {
    int x = 0;
    for (x = 0; x < 9; x++) {
        if (square->possible[x] == 0) {
            square->number = x + 1;
            square->solvable = 0;
            unsolved--;
        }
    }
    return 1;
}