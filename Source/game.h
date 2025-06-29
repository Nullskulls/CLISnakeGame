#ifndef GAME_H
#define GAME_H
#include "Edit_Board.h"
#include <stdbool.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdio.h>

int get_input(gameBoard* gamestate);
void hide_cursor(void);
int get_input_blocking(void);
void move(gameBoard* gamestate, const char key);
void change_board(const gameBoard* gamestate);
void change_current(const gameBoard* gamestate);
int is_valid_move(const gameBoard* gamestate, const int* coords);
void exiter(gameBoard* gamestate, char* text);


#endif //GAME_H
