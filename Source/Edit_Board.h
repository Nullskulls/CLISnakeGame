#ifndef EDIT_BOARD_H
#define EDIT_BOARD_H
#include <stdbool.h>
#define BOARD_ROWS 20
#define BOARD_COLS 40

typedef struct {
    int x;
    int y;
}coords;

typedef struct {
    int* head;
    int apple_count;
    char** board;
    int length;
    coords* history;
    coords* current;
} gameBoard;

bool is_snake(const gameBoard* gamestate, const int* coords);
void place_apple(gameBoard* gamestate);
int set_block(const gameBoard* gamestate, int row, int col, char block);
void fillBoard(const gameBoard* gamestate);
int* random_cord(void);
void setupBoard(gameBoard* gamestate);
gameBoard* initializeBoard(void);
void wipe_board(gameBoard* gamestate);
bool is_prev(const gameBoard* gamestate, const int* coords);

#include "game.h"
#endif
