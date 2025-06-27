#ifndef GAME_H
#define GAME_H
#include "Edit_Board.h"
#include <stdbool.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

void set_new_pos(gameBoard* gamestate, char key);
bool is_valid(char key, const gameBoard* const gamestate);
int get_input(void);
void hide_cursor(void);
int get_input_blocking(void);

#endif //GAME_H
