#include<stdio.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "game_logic.h"

using namespace std;


int main(){
    const int width = BoardWidth, height = BoardHeight, cell_size = 30;
    const int window_width = 800, window_height = 600;
    // Store settled cells separately from the currently falling piece.
    bool boardGrid[height][width] = { false };

    // The initial piece is a square with a position in board coordinates.
    bool piece[PieceHeight][PieceWidth] = { true, true, true, true };
    int pieceRow = 0, pieceCol = width / 2 - 1;

    // Start the SDL video subsystem before creating any windows.
    const int initResult = SDL_Init(SDL_INIT_VIDEO);
    if (initResult != 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create the initial play area; rendering will be added later.
    SDL_Window* window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);

    if (!window) {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }


    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) {
        printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Keep the application alive until the user closes the window.
    bool running = true;

    // Gravity moves the piece once this many milliseconds have elapsed.
    Uint32 lastDropTime = SDL_GetTicks();
    const Uint32 dropInterval = 500;

    while(running){
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } 
            else if (event.type == SDL_KEYDOWN) {
                // Test each requested move before changing the piece position.
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        if (canPlacePiece(boardGrid, piece, pieceRow, pieceCol - 1))
                            pieceCol--;
                        break;
                    case SDLK_RIGHT:
                        if (canPlacePiece(boardGrid, piece, pieceRow, pieceCol + 1))
                            pieceCol++;
                        break;
                    case SDLK_DOWN:
                        if (canPlacePiece(boardGrid, piece, pieceRow + 1, pieceCol)) {
                            pieceRow++;
                        } else {
                            lockPiece(boardGrid, piece, pieceRow, pieceCol);
                        }
                        break;
                }
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastDropTime >= dropInterval) {
            // Automatic falling uses the same collision rule as the Down key.
            if (canPlacePiece(boardGrid, piece, pieceRow + 1, pieceCol)) {
                pieceRow++;
            } else {
                lockPiece(boardGrid, piece, pieceRow, pieceCol);
            }
            lastDropTime = currentTime;
        }

        // Render the SDL background
        SDL_SetRenderDrawColor(renderer, 8, 11, 64, 255);
        SDL_RenderClear(renderer);

        // Draw the board centered inside the window.
        const int boardWidth = width * cell_size;
        const int boardHeight = height * cell_size;
        const int boardX = (window_width - boardWidth) / 2;

        SDL_Rect board = { boardX, 0, boardWidth, boardHeight };
        SDL_SetRenderDrawColor(renderer, 23, 23, 22, 255);
        SDL_RenderFillRect(renderer, &board);

        // Draw cells that have already landed on the board.
        SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
        for (int boardRow = 0; boardRow < height; boardRow++) {
            for (int boardColumn = 0; boardColumn < width; boardColumn++) {
                if (boardGrid[boardRow][boardColumn]) {
                    SDL_Rect cell = {
                        boardX + boardColumn * cell_size,
                        boardRow * cell_size,
                        cell_size,
                        cell_size
                    };
                    SDL_RenderFillRect(renderer, &cell);
                }
            }
        }

        // Draw the active piece separately so it can still move.
        for (int i = 0; i < PieceHeight; i++) {
            for (int j = 0; j < PieceWidth; j++) {
                if (piece[i][j]) {
                    SDL_Rect cell = { boardX + (pieceCol + j) * cell_size, (pieceRow + i) * cell_size, cell_size, cell_size };
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                    SDL_RenderFillRect(renderer, &cell);
                }
            }
        }

        // Draw the grid lines for the board.
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i <= width; i++) {
            int x = boardX + i * cell_size;
            SDL_RenderDrawLine(renderer, x, 0, x, boardHeight);
        }
        for (int i = 0; i <= height; i++) {
            int y = i * cell_size;
            SDL_RenderDrawLine(renderer, boardX, y, boardX + boardWidth, y);
        }

        SDL_RenderPresent(renderer);
        
        SDL_Delay(16); // Limit the loop to roughly 60 iterations per second.
    }


    // Release SDL resources in the reverse order of setup.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}