#include "sudoku.h"

int box_singles(Square ***sudoku, Box **boxes) {
    int i = 0;
    int j = 0;
    int x = 0;
    int count = 0;
    int temp = 0;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            count = 0;
            for (x = 0; x < 9; x++) {
                if (boxes[i]->squares[x]->number != 0) {
                    continue;
                }
                if (boxes[i]->squares[x]->possible[j] == 0) {
                    count++;
                    temp = x;
                }
                if (count == 2) {
                    break;
                }
            }
            if (count == 1) {
                boxes[i]->squares[temp]->number = j + 1;
                unsolved--;
                boxes[i]->squares[temp]->solvable = 0;
                update_sudoku(sudoku, boxes[i]->squares[temp]->row, boxes[i]->squares[temp]->column);
                return 1;
            }
        }
    }
    return 0;
}

Box **create_boxes() {
    Box **boxes = NULL;
    int x = 0;
    int y = 0;
    boxes = malloc(sizeof(Box *) * 9);
    for (x = 0; x < 9; x++) {
        boxes[x] = malloc(sizeof(Box));
        boxes[x]->squares = malloc(sizeof(Square *) * 9);
        boxes[x]->numbers = 0;
        boxes[x]->solvable = 9;
        boxes[x]->next = NULL;
        for (y = 0; y < 9; y++) {
            boxes[x]->possible[y] = 0;
        }
    }
    return boxes;
}

int update_boxes(Square ***sudoku, int row, int col) {
    int x = 0;
    int number = sudoku[row][col]->number;
    Box *box = sudoku[row][col]->box;
    for (x = 0; x < 9; x++) {
        if (box->squares[x]->possible[number - 1] == 0) {
            box->squares[x]->solvable--;
            box->squares[x]->possible[number - 1] = 1;
        }
    }

    return 1;
}