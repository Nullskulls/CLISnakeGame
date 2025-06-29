#include <stdio.h>
#include <stdlib.h>
#include "Edit_Board.h"

#include "Draw.h"
#include "game.h"

int set_block(const gameBoard* gamestate, int row, int col, char block) {
    if (row < BOARD_ROWS && col < BOARD_COLS && (gamestate->board[row][col] == ' ' || gamestate->board[row][col] == 'A')) {
        gamestate->board[row][col] = block;
        return 0;
    }
    return -1;
}

void fillBoard(const gameBoard* gamestate) {
    for (int i = 0; i < BOARD_ROWS; i++) {
        for (int j = 0; j < BOARD_COLS; j++) {
            if (gamestate->board[i][j] == 'A') {continue;}
            gamestate->board[i][j] = ' ';
        }
    }
}

bool is_prev(const gameBoard* gamestate, const int* coords) {
    if (coords[0] == gamestate->current[0].x && coords[1] == gamestate->current[0].y) {
        return true;
    }
    return false;
}

bool is_snake(const gameBoard* gamestate, const int* coords) {
    for (int i = 1; i < gamestate->length+1; i++) {
        if (gamestate->head[0] == coords[0] && gamestate->head[1] == coords[1]) {
            return true;
        } else if (gamestate->current[i].x == coords[0] && gamestate->current[i].y == coords[1]) {
            return true;
        }
    }
    return false;
}

void place_apple(gameBoard* gamestate) {
    gamestate->apple_count++;
    int* apple_cords = random_cord();
    while (is_snake(gamestate, apple_cords)) {
        free(apple_cords);
        apple_cords = random_cord();
    }
    gamestate->board[apple_cords[0]][apple_cords[1]] = 'A';
    free(apple_cords);
    if (gamestate->apple_count < gamestate->length) {
        place_apple(gamestate);
        printf("%i", gamestate->apple_count);
    }
}

void wipe_board(gameBoard* gamestate) {
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
    cords[0] = rand() % BOARD_ROWS;
    cords[1] = rand() % BOARD_COLS;
    return cords;
}

void setupBoard(gameBoard* gamestate) {
    gamestate->head = random_cord();
    wipe_board(gamestate);
    gamestate->board[gamestate->head[0]][gamestate->head[1]] = '@';
    gamestate->length = 0;
    gamestate->apple_count = 0;
    place_apple(gamestate);
}


gameBoard* initializeBoard(void) {
    gameBoard* gamestate = malloc(sizeof(gameBoard));
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
    gamestate->history = calloc(BOARD_ROWS * BOARD_COLS, sizeof(coords));
    for (int i = 0; i < BOARD_ROWS * BOARD_COLS; i++) {
        gamestate->history[i].y--;
        gamestate->history[i].x--;
    }
    gamestate->current = calloc(BOARD_ROWS * BOARD_COLS, sizeof(coords));
    for (int i = 0; i < BOARD_ROWS * BOARD_COLS; i++) {
        gamestate->current[i].y--;
        gamestate->current[i].x--;
    }
    gamestate->board = board;
    setupBoard(gamestate);
    return gamestate;
}

