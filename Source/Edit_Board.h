#ifndef EDIT_BOARD_H
#define EDIT_BOARD_H

#define BOARD_ROWS 20
#define BOARD_COLS 40

typedef struct {
    int x;
    int y;
}coords;

typedef struct {
    int* head;
    char** board;
    int length;
    coords* history;
    coords* current;
} gameBoard;

int set_block(gameBoard* gamestate, int row, int col, char block);
void fillBoard(const gameBoard* gamestate);
int* random_cord(void);
void setupBoard(gameBoard* gamestate);
gameBoard initializeBoard(void);

#endif
