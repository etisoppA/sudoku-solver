#include "sudoku.h"

Sudoku *create_sudoku(Square ***squares, Box **boxes) {
    Sudoku *sudoku;
    sudoku = malloc(sizeof(sudoku));
    sudoku->squares = squares;
    sudoku->boxes = boxes;
    return sudoku;
}

int **read_puzzle(char path[15]) {
    int **puzzle = NULL;
    int i = 0;
    int j = 0;
    if (path == NULL) {
        printf("Path is null\n");
        return NULL;
    }
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return NULL;
    }
    int array[9][9] = {0};
    for (i = 0; i < 9; i++) {
        fscanf(fp, "%d %d %d %d %d %d %d %d %d\n", &array[i][0], &array[i][1], &array[i][2], &array[i][3],
               &array[i][4], &array[i][5], &array[i][6], &array[i][7], &array[i][8]);
    }
    fclose(fp);
    fp = NULL;
    puzzle = (int **) malloc(sizeof(int *) * 9);
    for (i = 0; i < 9; i++) {
        puzzle[i] = (int *) malloc(sizeof(int) * 9);
        for (j = 0; j < 9; j++) {
            puzzle[i][j] = array[i][j];
        }
    }
    return puzzle;
}

int check_puzzle(Square ***sudoku, Box **boxes) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j]->solvable == 1) {
                solve_square(sudoku[i][j]);
                update_sudoku(sudoku, i, j);
                update_boxes(sudoku, i, j);
                return 1;
            }
        }
    }
    if (box_singles(sudoku, boxes) == 1) {
        return 1;
    }
    return check_rows(sudoku, boxes);
}

int update_sudoku(Square ***sudoku, int row, int col) {
    int x = 0;
    int number = sudoku[row][col]->number;
    for (x = 0; x < 9; x++) {
        if (sudoku[x][col]->possible[number - 1] == 0) {
            sudoku[x][col]->solvable--;
        }
        sudoku[x][col]->possible[number - 1] = 1;
    }
    for (x = 0; x < 9; x++) {
        if (sudoku[row][x]->possible[number - 1] == 0) {
            sudoku[row][x]->solvable--;
        }
        sudoku[row][x]->possible[number - 1] = 1;
    }
    return 1;
}

Sudoku *setup_board(int **puzzle) {
    int i = 0;
    int j = 0;
    int x = 0;
    int current_box = 0;
    Square ***sudoku = NULL;
    Box **boxes = NULL;
    sudoku = (Square ***) malloc(sizeof(Square **) * 9);
    boxes = create_boxes();
    for (i = 0; i < 9; i++) {
        sudoku[i] = (Square **) malloc(sizeof(Square *) * 9);
        for (j = 0; j < 9; j++) {
            sudoku[i][j] = (Square *) malloc(sizeof(Square) * 9);
            sudoku[i][j]->number = puzzle[i][j];
            sudoku[i][j]->row = i;
            sudoku[i][j]->column = j;
            sudoku[i][j]->solvable = 9;
            boxes[current_box]->squares[boxes[current_box]->numbers] = sudoku[i][j];
            sudoku[i][j]->box = boxes[current_box];
            boxes[current_box]->numbers++;
            for (x = 0; x < 9; x++) {
                sudoku[i][j]->possible[x] = 0;
            }
            if (j == 2 || j == 5) {
                current_box++;
            }
        }
        current_box -= 2;
        if (i == 2) {
            current_box = 3;
        }
        if (i == 5) {
            current_box = 6;
        }
    }
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (sudoku[i][j]->number != 0) {
                sudoku[i][j]->solvable = 0;
                update_sudoku(sudoku, i, j);
                update_boxes(sudoku, i, j);
                unsolved--;
            }
        }
    }
    return create_sudoku(sudoku, boxes);
}

void print_puzzle(Square ***puzzle) {
    int i = 0;
    int j = 0;
    printf("-------------------------------\n");
    for (i = 0; i < 9; i++) {
        printf("|");
        for (j = 0; j < 9; j++) {
            printf(" %d ", puzzle[i][j]->number);
            if (((j + 1) % 3) == 0) {
                printf("|");
            }
        }
        printf("\n");
        if (((i + 1) % 3) == 0) {
            printf("-------------------------------\n");
        }
    }
}