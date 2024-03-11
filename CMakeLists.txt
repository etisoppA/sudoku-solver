cmake_minimum_required(VERSION 3.27)
project(sudoku_solver C)

set(CMAKE_C_STANDARD 11)

add_executable(sudoku_solver
        sudoku.c
        sudoku.h
        puzzle.c
        square.c
        box.c
        row.c)
