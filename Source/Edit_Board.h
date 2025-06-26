#ifndef EDIT_BOARD_H
#define EDIT_BOARD_H

#define BOARD_ROWS 20
#define BOARD_COLS 40


typedef struct {
    int* head;
    char** board;
    int length;
} gameBoard;

int set_block(const gameBoard* gamestate, int row, int col, char block);
void fillBoard(const gameBoard* gamestate);
int* random_cord(void);
void setupBoard(gameBoard* gamestate);
gameBoard initializeBoard(void);

#endif
