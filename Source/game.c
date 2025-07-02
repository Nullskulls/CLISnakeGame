#include "game.h"
/*
 Function used to exit properly freeing all dynamically allocated memory (assuming user doesn't alt f4 lol)
 */
void exiter(gameBoard* gamestate, char* text) {
    //start by freeing coords of snake head
    free(gamestate->head);
    //free current and history
    free(gamestate->current);
    //for row in board rows
    for (int i = 0; i < BOARD_ROWS; i++) {
        //free columns in row
        free(gamestate->board[i]);
    }
    //free rows in board
    free(gamestate->board);
    //print message
    system("cls");
    printf("%s", text);
    //stop app so user can read
    Sleep(2000);
    //exit with code 0
    exit(0);
}

int get_input(gameBoard* gamestate){
    if (kbhit()) {
        char key = getch();
        switch (key) {
            case 'w': return 1;
            case 'a': return 2;
            case 's': return 3;
            case 'd': return 4;
            case 27: {
                printf("Exiting...\n");
                free(gamestate->head);
                for (int i = 0; i < BOARD_ROWS * BOARD_COLS; i++) {
                    free(gamestate->current);
                }
                for (int i = 0; i < BOARD_ROWS; i++) {
                    free(gamestate->board[i]);
                }
                free(gamestate->board);
                exit(0);
            }
            default: return 0;
        }
    }
    return 0;
}



void hide_cursor(void) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}


int get_input_blocking(void) {
    printf("Enter direction (w/a/s/d or ESC to quit): ");
    char key = getchar();

    switch (key) {
        case 'w': return 1;
        case 'a': return 2;
        case 's': return 3;
        case 'd': return 4;
        case 27:  return 5;
        default: return 0;
    }
}

int is_valid_move(const gameBoard* gamestate, const int* coords) {
    if (is_snake(gamestate, coords)) {
        return -1;
    }else if (0 > coords[0] || coords[0] >= 40 || 0 > coords[1] || coords[1] >= 40) {
        return 1;
    }else if (is_prev(gamestate, coords) == true) {
        return -2;
    }
    return 0;
}

void change_current(const gameBoard* gamestate) {
    coords* holder = malloc(sizeof(coords)*gamestate->length+1);
    if (holder  == NULL) {
        printf("Memory allocation error");
        exit(1);
    }
    for (int i = 0; i < gamestate->length+1; i++) {
        holder[i].x = gamestate->current[i].x;
        holder[i].y = gamestate->current[i].y;
    }
    gamestate->current[0].x = gamestate->head[0];
    gamestate->current[0].y = gamestate->head[1];
    for (int i = 1; i < gamestate->length+1; i++) {
        gamestate->current[i].x = holder[i-1].x;
        gamestate->current[i].y = holder[i-1].y;
    }
    free(holder);

}

void change_board(const gameBoard* gamestate) {
    fillBoard(gamestate);
    set_block(gamestate, gamestate->head[0], gamestate->head[1], '@');
    for (int i = 0; i < gamestate->length+1; i++) {
        set_block(gamestate, gamestate->current[i].x, gamestate->current[i].y, '#');
    }
}

int move(gameBoard* gamestate, const char key) {
    int* holder = malloc(sizeof(int)*2);
    if (holder == NULL) {
        printf("Memory allocation error");
        exit(1);
    }
    switch (key) {
        case 1: {
            holder[0] = gamestate->head[0]-1;
            holder[1] = gamestate->head[1];
            break;
        }
            case 2: {
            holder[0] = gamestate->head[0];
            holder[1] = gamestate->head[1]-1;
            break;
        }
            case 3: {
            holder[0] = gamestate->head[0]+1;
            holder[1] = gamestate->head[1];
            break;
        }
            case 4: {
            holder[0] = gamestate->head[0];
            holder[1] = gamestate->head[1]+1;
            break;
        }
        default: {
            free(holder);
            return;
        }
    }
    int validation = is_valid_move(gamestate, holder);
    if (validation == 1 || validation == -1) {
        exiter(gamestate, "You lost.");
    }else if (validation == 0) {
        if (gamestate->board[holder[0]][holder[1]] == 'A') {
            gamestate->length++;
            gamestate->apple_count--;
            place_apple(gamestate);
        }
        change_current(gamestate);
        gamestate->head[0] = holder[0];
        gamestate->head[1] = holder[1];
    } else if (validation == -2) {
        return -1;
    }
    free(holder);
    change_board(gamestate);
    return 0;
}
