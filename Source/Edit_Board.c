#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Edit_Board.h"

int set_block(const gameBoard* gamestate, int row, int col, char block) {
    if (row < BOARD_ROWS && col < BOARD_COLS && gamestate->board[row][col] == ' ') {
        gamestate->board[row][col] = block;
        return 0;
    }
    return -1;
}

void fillBoard(const gameBoard* gamestate) {
    for (int i = 0; i < BOARD_ROWS; i++) {
        for (int j = 0; j < BOARD_COLS; j++) {
            gamestate->board[i][j] = ' ';
        }
    }
}


int* random_cord(void) {
    int* cords = malloc(sizeof(int) * 2);
    if (cords == NULL){
        printf("Allocation error\n");
        exit(1);
    }
    srand(time(NULL));
    cords[0] = rand() % BOARD_ROWS;
    cords[1] = rand() % BOARD_COLS;
    return cords;
}

void setupBoard(gameBoard* gamestate) {
    gamestate->head = random_cord();
    fillBoard(gamestate);
    gamestate->board[gamestate->head[0]][gamestate->head[1]] = '@';
    gamestate->length = 1;
}


gameBoard initializeBoard(void) {
    gameBoard gamestate;
    char** board = malloc(sizeof(char*) * BOARD_ROWS);
    if (board == NULL){
        printf("Failed to allocate memory for board\n");
        exit(1);
    }
    for (int i = 0; i < BOARD_ROWS; i++) {
        board[i] = malloc(sizeof(char) * BOARD_COLS);
        if (board[i] == NULL) {
            printf("Failed to allocate memory for board\n");
            exit(1);
        }
    }
    gamestate.board = board;
    setupBoard(&gamestate);
    return gamestate;
}

