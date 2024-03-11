#include "sudoku.h"

int check_rows(Square ***sudoku, Box **boxes) {
    int i = 0;
    int j = 0;
    int k = 0;
    int sum[9];
    int place[9];
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            place[j] = 0;
            sum[j] = 0;
        }
        for (j = 0; j < 9; j++) {
            if (sudoku[i][j]->number != 0) {
                continue;
            }
            for (k = 0; k < 9; k++) {
                if (sudoku[i][j]->possible[k] == 0) {
                    sum[k]++;
                    place[k] = j;
                }
            }
        }
        for (j = 0; j < 9; j++) {
            if (sum[j] == 1) {
                sudoku[i][place[j]]->number = j + 1;
                sudoku[i][place[j]]->solvable = 0;
                unsolved--;
                update_sudoku(sudoku, i, place[j]);
                update_boxes(sudoku, i, place[j]);
                return 1;
            }
        }
    }
    return 0;
}