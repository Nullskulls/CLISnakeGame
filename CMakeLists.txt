cmake_minimum_required(VERSION 3.10)
project(CLISnakeGame C)

set(CMAKE_C_STANDARD 99)

add_executable(CLISnakeGame
        source/main.c
        source/Edit_Board.c
        source/Draw.c
)
