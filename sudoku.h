#ifndef SUDOKU_SOLVER_SUDOKU_H
#define SUDOKU_SOLVER_SUDOKU_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern int unsolved;

typedef struct Sudoku {
    struct Square ***squares;
    struct Box **boxes;
} Sudoku;

typedef struct Box {
    struct Square **squares;
    int numbers;
    int possible[9];
    int solvable;
    struct Box *next;
} Box;

typedef struct Square {
    int number;
    int possible[9];
    int solvable;
    Box *box;
    int row;
    int column;
} Square;

int **create_puzzle();
void print_puzzle(Square ***puzzle);
Sudoku *setup_board(int **puzzle);
Sudoku *create_sudoku(Square ***squares, Box **boxes);
int check_puzzle(Square ***sudoku, Box **boxes);
int solve_square(Square *square);
int update_sudoku(Square ***sudoku, int row, int col);
Box **create_boxes();
int update_boxes(Square ***sudoku, int row, int col);
int box_singles(Square ***sudoku, Box **boxes);
int check_rows(Square ***sudoku, Box **boxes);

#endif //SUDOKU_SOLVER_SUDOKU_H
