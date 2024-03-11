#include "sudoku.h"

int unsolved = 81;

int main() {
    int **puzzle = NULL;
    int progress = 0;
    Sudoku *sudoku = NULL;
    printf("Enter file name:\n");
    char path[15];
    scanf("%14s", path);
    puzzle = read_puzzle(path);
    if (puzzle == NULL) {
        printf("Failed to read puzzle\n");
        return 0;
    }
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