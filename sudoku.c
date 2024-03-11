#include "sudoku.h"

int unsolved = 81;

int main() {
    int **puzzle = NULL;
    int progress = 0;
    Sudoku *sudoku = NULL;
    puzzle = create_puzzle();
    sudoku = setup_board(puzzle);
    print_puzzle(sudoku->squares);
    while (unsolved > 0) {
        progress = check_puzzle(sudoku->squares, sudoku->boxes);
        if (progress == 0) {
            printf("Failed to solve\n");
            break;
        }
    }

    printf("\n");
    print_puzzle(sudoku->squares);
    return 0;
}