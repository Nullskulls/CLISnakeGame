#include <stdio.h>
#include "Edit_Board.h"

/*
 Function used to draw the game board
 */
void draw_game(const gameBoard* const gamestate) {
    //print how to exit to user
    printf("Press \"ESC\" to exit!\n");
    //for board column +2 (the plus two are because normally it doesn't span properly due to the corners
    for (int i = 0; i < BOARD_COLS+2; i++) {
        //print '*' used as a border marker
        printf("*");
    }
    //start new line
    printf("\n");
    //for row
    for (int i = 0; i < BOARD_ROWS; i++) {
        //print '*' (used as border)
        printf("*");
        //for column in row
        for (int j = 0; j < BOARD_COLS; j++) {
            //print index i, j of the board
            printf("%c", gamestate->board[i][j]);
        }
        //print border and start new line
        printf("*\n");
    }
    //draw bottom border
    for (int i = 0; i < BOARD_COLS+2; i++) {
        printf("*");
    }
    printf("\n");
}