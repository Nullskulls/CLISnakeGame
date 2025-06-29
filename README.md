# CLISnakeGame

A terminal-based implementation of the classic Snake game written in C. This is a beginner-friendly project focused on mastering memory management, pointers, and dynamic 2D arrays in a command-line interface.

## Features

- Fully playable Snake game in the terminal
- Dynamic memory handling for board, snake position, and apple placement
- Collision detection (walls and self)
- Snake growth on apple consumption
- Apple respawning system with ratio logic
- Custom board drawing and frame refreshing
- Memory cleanup on exit

## Controls

- `W` - Move up
- `A` - Move left
- `S` - Move down
- `D` - Move right
- `ESC` - Exit game

## Requirements

- A C compiler (e.g., GCC or Clang)
- Windows terminal or MinGW (due to Windows-specific functions like `getch()` and `Sleep()`)

## Build Instructions

```bash
mkdir build
cd build
cmake ..
make
```

## Run the Game

```bash
./CLISnakeGame
```

## Project Structure

```
.
├── Source/
│   ├── Draw.c / .h
│   ├── Edit_Board.c / .h
│   ├── game.c / .h
│   └── main.c
├── CMakeLists.txt
├── LICENSE
└── README.md
```

## Acknowledgements

Built from scratch as a first personal project in C. Expect bugs, memory leaks (hopefully fewer now), and chaos. Feedback is welcome.
