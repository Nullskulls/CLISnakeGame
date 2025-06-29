#include "game.h"
#include "Edit_Board.h"
#include "Draw.h"
int main(void) {
    gameBoard* gamestate = initializeBoard();
    hide_cursor();
    while (true) {
        char key = get_input(gamestate);
        while (!kbhit()) {
            move(gamestate, key);
            draw_game(gamestate);
            system("cls");
        }
    }
}
