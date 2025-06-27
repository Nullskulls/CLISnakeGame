#include "Edit_Board.h"
#include "Draw.h"
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "game.h"

int main(void) {
    srand(time(NULL));
    gameBoard gamestate = initializeBoard();
    hide_cursor();
    SetConsoleTitle("Snake..");
    int key;
    while (1){
        key = get_input();
        if (key == 5) {
            exit(0);
        }
        int key_holder = key;
        while (!kbhit()) {
            set_new_pos(&gamestate, key_holder);
            system("cls");
            draw_game(&gamestate);
            Sleep(150);
        }


    }
}
