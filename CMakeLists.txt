cmake_minimum_required(VERSION 3.10)
project(CLISnakeGame C)

set(CMAKE_C_STANDARD 99)

add_executable(CLISnakeGame
        Source/main.c
        Source/Edit_Board.c
        Source/Draw.c
        Source/game.c
)
