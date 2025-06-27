#include <stdio.h>
#include "Edit_Board.h"


void draw_game(const gameBoard* const gamestate) {
    printf("Press \"ESC\" to exit!\n");
    for (int i = 0; i < BOARD_COLS+2; i++) {
        printf("*");
    }
    printf("\n");
    for (int i = 0; i < BOARD_ROWS; i++) {
        printf("*");
        for (int j = 0; j < BOARD_COLS; j++) {
            printf("%c", gamestate->board[i][j]);
        }
        printf("*\n");
    }
    for (int i = 0; i < BOARD_COLS+2; i++) {
        printf("*");
    }
    printf("\n");
}