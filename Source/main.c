#include "Edit_Board.h"
#include <stdio.h>

int main(void) {
    gameBoard game = initializeBoard();

    // Print the board for fun
    for (int i = 0; i < BOARD_ROWS; i++) {
        for (int j = 0; j < BOARD_COLS; j++) {
            printf("%c", game.board[i][j]);
        }
        printf("\n");
    }

    return 0;
}
