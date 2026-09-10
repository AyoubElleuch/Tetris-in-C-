# Tetris in C++

This is Tetris made by me in C++ and coded by hand using my C++ knowledge and SDL documentation to build the graphics.

This is a fun project and a way to showcase my C++ game-development skills beyond the competitive-programming solutions in my [Competitive Programming Solutions](https://github.com/AyoubElleuch/Competitive-Programming-Solutions) repository.

This project is still actively being worked on and is nowhere near finished. You are welcome to clone it, play it, or contribute. I will read every pull request and consider it for inclusion.

## Current Features

- Falling, movable, and rotatable tetrominoes
- Collision detection and locked pieces
- Full-line clearing
- Next-piece preview
- Game-over overlay and restart button
- Keyboard restart with `R` or `Enter`

## Controls

| Key | Action |
| --- | --- |
| Left Arrow | Move left |
| Right Arrow | Move right |
| Down Arrow | Move down |
| Up Arrow | Rotate |
| `R` or `Enter` | Restart after game over |

## Requirements

- A C++17 compiler
- CMake 3.10 or later
- SDL2
- SDL2_ttf

The current CMake setup was developed with MSYS2 UCRT64 on Windows, using Ninja and the UCRT64 versions of SDL2 and SDL2_ttf.

## Build and Run

From an MSYS2 UCRT64 terminal, install the dependencies:

```sh
pacman -S mingw-w64-ucrt-x86_64-SDL2 mingw-w64-ucrt-x86_64-SDL2_ttf mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja
```

Configure, build, and run from the project directory:

```sh
cmake -S . -B build -G Ninja
cmake --build build
./build/Tetris.exe
```

The game currently opens Arial from `C:/Windows/Fonts/arial.ttf`, so this setup is presently Windows-specific.

## Contributing

Contributions, fixes, and ideas are welcome. Please open a pull request with a clear description of what you changed. I will read every contribution request and review it for the project.

## Project Status

Work in progress. Expect incomplete features and changes as the game develops.
