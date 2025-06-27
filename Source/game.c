#include "game.h"

int get_input(void){
    if (kbhit()) {
        char key = getch();
        switch (key) {
            case 'w': return 1;
            case 'a': return 2;
            case 's': return 3;
            case 'd': return 4;
            case 27: return 5;
            default: return 0;
        }
    }
    return 0;
}

bool is_valid(char key, const gameBoard* const gamestate) {
    int* head = gamestate->head;
    int new_pos[2];
    switch (key) {
        case 1: {
            new_pos[0] = head[0]-1;
            new_pos[1] = head[1];
            break;
        }
            case 2: {
            new_pos[0] = head[0];
            new_pos[1] = head[1]-1;
            break;
        }
            case 3: {
            new_pos[0] = head[0]+1;
            new_pos[1] = head[1];
            break;
        }
            case 4: {
            new_pos[0] = head[0];
            new_pos[1] = head[1]+1;
            break;
        }
            default: {
            return false;
        }
    }
    if (new_pos[0] >= 20 || new_pos[1] >= 40) {
        return false;
    }
    for (int i = 0; i < gamestate->length; i++) {
        if (gamestate->current[i].x == -1) {
            return true;
        }
        if (gamestate->current[i].x == new_pos[0] && gamestate->current[i].y == new_pos[1]) {
            return false;
        }
    }
    return true;
}


void set_new_pos(gameBoard* gamestate, char key) {
    if (is_valid(key, gamestate)) {
        int* head = gamestate->head;
        int new_pos[2];
        switch (key) {
            case 1: {
                new_pos[0] = head[0]-1;
                new_pos[1] = head[1];
                break;
            }
            case 2: {
                new_pos[0] = head[0];
                new_pos[1] = head[1]-1;
                break;
            }
            case 3: {
                new_pos[0] = head[0]+1;
                new_pos[1] = head[1];
                break;
            }
            case 4: {
                new_pos[0] = head[0];
                new_pos[1] = head[1]+1;
                break;
            }
            default: {

            }
        }
        if (gamestate->board[new_pos[0]][new_pos[1]] == 'A') {
            int* apple_coords = random_cord();
            set_block(gamestate, apple_coords[0], apple_coords[1], 'A');
            free (apple_coords);
        }
        gamestate->history[0].x = gamestate->head[0];
        gamestate->history[0].y = gamestate->head[1];
        for (int i = 1; i < gamestate->length; i++) {
            gamestate->history[i].x = gamestate->current[i-1].x;
            gamestate->history[i].y = gamestate->current[i-1].y;
        }
        coords* holder = malloc(sizeof(coords)*gamestate->length);
        for (int i = 0; i < gamestate->length; i++) {
            holder[i].x = gamestate->current[i].x;
            holder[i].y = gamestate->current[i].y;
        }
        gamestate->current[0].x = head[0];
        gamestate->current[0].y = head[1];
        for (int i = 1; i < gamestate->length; i++) {
            gamestate->current[i].x = holder[i-1].x;
            gamestate->current[i].y = holder[i-1].y;
        }
        gamestate->head[0] = new_pos[0];
        gamestate->head[1] = new_pos[1];
        free(holder);
        fillBoard(gamestate);
        set_block(gamestate, gamestate->head[0], gamestate->head[1], '@');
        for (int i = 0; i < gamestate->length; i++) {
            set_block(gamestate, gamestate->current[i].x, gamestate->current[i].y, '=');
        }
    }
}


void hide_cursor(void) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

#include <stdio.h>

int get_input_blocking(void) {
    char key;
    printf("Enter direction (w/a/s/d or ESC to quit): ");
    key = getchar();

    switch (key) {
        case 'w': return 1;
        case 'a': return 2;
        case 's': return 3;
        case 'd': return 4;
        case 27:  return 5;  // ESC (won’t actually work in this mode unless raw)
        default: return 0;
    }
}
