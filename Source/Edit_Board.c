#include <stdio.h>
#include <stdlib.h>
#include "Edit_Board.h"
/*
  Function to set a specific tile on the game board to a specific block.
 */
int set_block(const gameBoard* gamestate, int row, int col, char block) {
    // if within bounds. (max row and max columns defined in the header)
    if (row < BOARD_ROWS && col < BOARD_COLS && (gamestate->board[row][col] == ' ' || gamestate->board[row][col] == 'A')) {
        // set the block on the board through indexing.
        gamestate->board[row][col] = block;
        // return 0  for successful. (not used)
        return 0;
    }
    // return -1 for failed/out of bounds (not used)
    return -1;
}
/*
 Function used to delete the snake from the board and skipping apples.
 */
void fillBoard(const gameBoard* gamestate) {
    // for every row.
    for (int i = 0; i < BOARD_ROWS; i++) {
        // for every column in row.
        for (int j = 0; j < BOARD_COLS; j++) {
            // if it's an apple: skip
            if (gamestate->board[i][j] == 'A') {continue;}
            //otherwise write over it (the snake)
            gamestate->board[i][j] = ' ';
        }
    }
}
/*
 Function to check if the current move is going backwards (in the sense that user
 is attempting to go inside the own snake if that makes sense) like think of the snake as
 @#### let's number it with H1234 H->head of the snake and numbers are the body.
 if the user is attempting to make the head be at point 1 they'd be attempting to go to the prev pos.
 this is a function to check if that is the case.
 */
bool is_prev(const gameBoard* gamestate, const int* coords) {
    // if user is attempting to go to prev.
    if (coords[0] == gamestate->current[0].x && coords[1] == gamestate->current[0].y) {
        // return true
        return true;
    }
    // otherwise: return false
    return false;
}
/*
 Function to check if the user hit their own tail.
 */
bool is_snake(const gameBoard* gamestate, const int* coords) {
    // for every number within 0->length+1
    for (int i = 1; i < gamestate->length+1; i++) {
        //if coords is at any index of current
        if (gamestate->current[i].x == coords[0] && gamestate->current[i].y == coords[1]) {
            //return true
            return true;
        }
    }
//if user somehow goes inside their own head (I legitimately don't know how they would, but I suspect it's possible)
    if (gamestate->head[0] == coords[0] && gamestate->head[1] == coords[1]) {
        //return true
        return true;
    }
    //return false if none are true
    return false;
}

/*
 Function used to handle placing apples onto the board. (usually called when an apple is eaten)
 */
void place_apple(gameBoard* gamestate) {
    //start by increasing apple count
    gamestate->apple_count++;
    //get a random row and col to place the apple
    int* apple_cords = random_cord();
    //while the apple's cords are on the snake
    while (is_snake(gamestate, apple_cords)) {
        //free the allocated memory so valgrind doesn't cuss me out
        free(apple_cords);
        //try placing an apple again
        apple_cords = random_cord();
    }
    //finally after the apple is not on the snake place it on the board
    gamestate->board[apple_cords[0]][apple_cords[1]] = 'A';
    //free the coords cuz memory leak
    free(apple_cords);
}

/*
 Function used to completely clean the board (because malloc likes giving me memory with apples already)
 */
void wipe_board(gameBoard* gamestate) {
    //for row in board
    for (int i = 0; i < BOARD_ROWS; i++) {
        //for column in row
        for (int j = 0; j < BOARD_COLS; j++) {
            //set the index i, j on the board to ' ' which is used as a placeholder for empty here
            gamestate->board[i][j] = ' ';
        }
    }
}

/*
 Function used to get random cords for spawning the snake and apples
 */
int* random_cord(void) {
    //allocate an int array of size 2
    int* cords = malloc(sizeof(int) * 2);
    //if malloc returns NULL (allocation failed)
    if (cords == NULL){
        //print to the user that it failed
        printf("Allocation error\n");
        //exit with code 1
        exit(1);
    }
    //otherwise add random ints into the allocated mem
    cords[0] = rand() % BOARD_ROWS;
    cords[1] = rand() % BOARD_COLS;
    //return the address/pointer
    return cords;
}
/*
 Function used to set up the board while initializing it.
 */
void setupBoard(gameBoard* gamestate) {
    //set the head to a random pos on the board
    gamestate->head = random_cord();
    //completely wipe the board
    wipe_board(gamestate);
    //place the head of the snake
    gamestate->board[gamestate->head[0]][gamestate->head[1]] = '@';
    //set snake length to 0
    gamestate->length = 0;
    //set apple count to 0
    gamestate->apple_count = 0;
    //place an apple (function increases apple count)
    place_apple(gamestate);
}

/*
 Function used to initialize the game state.
 */
gameBoard* initializeBoard(void) {
    //allocate memory for gamestate
    gameBoard* gamestate = malloc(sizeof(gameBoard));
    //if memory allocation fails
    if (gamestate == NULL) {
        //notify user
        printf("Allocation error\n");
        //exit with code 1
        exit(1);
    }
    //allocate board rows
    char** board = malloc(sizeof(char*) * BOARD_ROWS);
    //if malloc fails
    if (board == NULL){
        //notify user
        printf("Failed to allocate memory for board\n");
        //exit with code 1
        exit(1);
    }
    //for row in board
    for (int i = 0; i < BOARD_ROWS; i++) {
        //allocate columns inside each row
        board[i] = malloc(sizeof(char) * BOARD_COLS);
        //if memory allocation fails
        if (board[i] == NULL) {
            //notify user
            printf("Failed to allocate memory for board\n");
            //exit with code 1
            exit(1);
        }
    }
    //allocate clean memory for current
    gamestate->current = calloc(BOARD_ROWS * BOARD_COLS, sizeof(coords));
    //for index in current
    for (int i = 0; i < BOARD_ROWS * BOARD_COLS; i++) {
        //decrease x,y by one (to become {-1, -1} used as empty/NULL)
        gamestate->current[i].y--;
        gamestate->current[i].x--;
    }
    //make gamestate (board) point to the previously allocated board
    gamestate->board = board;
    //set up the board
    setupBoard(gamestate);
    //return the gamestate
    return gamestate;
}

