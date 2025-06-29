#include <time.h>

#include "game.h"
#include "Edit_Board.h"
#include "Draw.h"
int main(void) {
    char valid = 'e';
    srand(time(NULL));
    gameBoard* gamestate = initializeBoard();
    hide_cursor();
    system("cls");
    char key;
    char history;
    while (true) {
        key = get_input(gamestate);
        while (!kbhit()) {
            if (move(gamestate, key) == -1) {
                key = history;
            }
            draw_game(gamestate);
            Sleep(7);
            printf("\033[H");
        }
    history = key;
    }
}