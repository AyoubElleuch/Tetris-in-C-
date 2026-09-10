#include<stdio.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "game_logic.h"
#include "rendering.h"

int main(){
    const int width = BoardWidth, height = BoardHeight, cell_size = 30;
    const int window_width = 800, window_height = 600;
    const int preview_width = PieceWidth * cell_size,
                preview_height = PieceHeight * cell_size;
    // Store settled cells separately from the currently falling piece.
    bool boardGrid[height][width] = { false };

    bool piece[PieceHeight][PieceWidth] = {};
    int pieceRow = 0, pieceCol = width / 2 - 1;

    bool nextPiece[PieceHeight][PieceWidth] = {};

    chooseRandomPiece(piece);
    chooseRandomPiece(nextPiece);
    
    // Start the SDL video subsystem before creating any windows.
    const int initResult = SDL_Init(SDL_INIT_VIDEO);
    if (initResult != 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() != 0) {
        printf("TTF_Init failed: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    // Create the initial play area; rendering will be added later.
    SDL_Window* window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);

    if (!window) {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }


    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) {
        printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    TTF_Font* overlayFont = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 46);
    TTF_Font* buttonFont = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 24);
    if (!overlayFont || !buttonFont) {
        printf("TTF_OpenFont failed: %s\n", TTF_GetError());
        if (overlayFont) TTF_CloseFont(overlayFont);
        if (buttonFont) TTF_CloseFont(buttonFont);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Keep the application alive until the user closes the window.
    bool running = true;
    bool gameOver = false;
    const SDL_Rect restartButton = { window_width / 2 - 90, 360, 180, 52 };

    // Gravity moves the piece once this many milliseconds have elapsed.
    Uint32 lastDropTime = SDL_GetTicks();
    const Uint32 dropInterval = 200;

    const auto resetGame = [&]() {
        restartGame(boardGrid, pieceRow, pieceCol);
        chooseRandomPiece(piece);
        chooseRandomPiece(nextPiece);
        gameOver = false;
        lastDropTime = SDL_GetTicks();
    };

    while (running) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (gameOver && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                const int mouseX = event.button.x;
                const int mouseY = event.button.y;
                if (mouseX >= restartButton.x && mouseX < restartButton.x + restartButton.w &&
                    mouseY >= restartButton.y && mouseY < restartButton.y + restartButton.h) {
                    resetGame();
                }
            }
            else if (gameOver && event.type == SDL_KEYDOWN &&
                     (event.key.keysym.sym == SDLK_r || event.key.keysym.sym == SDLK_RETURN)) {
                resetGame();
            }
            else if (event.type == SDL_KEYDOWN && !gameOver) {
                // Test each requested move before changing the piece position.
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        if (validRotatePiece(boardGrid, piece, pieceRow, pieceCol))
                            rotatePiece(piece);
                        break;
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
                            clearFullLines(boardGrid);
                            copyPiece(nextPiece, piece);
                            chooseRandomPiece(nextPiece);
                            gameOver = isGameOver(boardGrid, piece);
                        }
                        break;
                }
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastDropTime >= dropInterval && !gameOver) {
            // Automatic falling uses the same collision rule as the Down key.
            if (canPlacePiece(boardGrid, piece, pieceRow + 1, pieceCol)) {
                pieceRow++;
            } else {
                lockPiece(boardGrid, piece, pieceRow, pieceCol);
                clearFullLines(boardGrid);
                copyPiece(nextPiece, piece);
                chooseRandomPiece(nextPiece);
                gameOver = isGameOver(boardGrid, piece);
            }
            lastDropTime = currentTime;
        }

        // Render the SDL background
        SDL_SetRenderDrawColor(renderer, 8, 11, 64, 255);
        SDL_RenderClear(renderer);


        // Render the Preview Piece
        SDL_Rect previewRect = { 10, 10, preview_width, preview_height };
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &previewRect);

        
        // Draw the preview piece in the preview area.
        for (int i = 0; i < PieceHeight; i++) {
            for (int j = 0; j < PieceWidth; j++) {
                if (nextPiece[i][j]) {
                    SDL_Rect cell = { 10 + j * cell_size, 10 + i * cell_size, cell_size, cell_size };
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                    SDL_RenderFillRect(renderer, &cell);
                }
            }
        }

        // Draw the grid lines for the preview area.
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i <= preview_width / cell_size; i++) {
            int x = 10 + i * cell_size;
            SDL_RenderDrawLine(renderer, x, 10, x, 10 + preview_height);
        }
        for (int i = 0; i <= preview_height / cell_size; i++) {
            int y = 10 + i * cell_size;
            SDL_RenderDrawLine(renderer, 10, y, 10 + preview_width, y);
        }

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
        if (!gameOver) { 
            for (int i = 0; i < PieceHeight; i++) {
                for (int j = 0; j < PieceWidth; j++) {
                    if (piece[i][j]) {
                        SDL_Rect cell = { boardX + (pieceCol + j) * cell_size, (pieceRow + i) * cell_size, cell_size, cell_size };
                        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                        SDL_RenderFillRect(renderer, &cell);
                    }
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

        if (gameOver) {
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 190);
            SDL_Rect overlay = { boardX, 0, boardWidth, boardHeight };
            SDL_RenderFillRect(renderer, &overlay);

            drawText(renderer, overlayFont, "Game Over", window_width / 2, 245, { 255, 255, 255, 255 });

            SDL_SetRenderDrawColor(renderer, 220, 48, 48, 255);
            SDL_RenderFillRect(renderer, &restartButton);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &restartButton);
            drawText(renderer, buttonFont, "Restart", window_width / 2, restartButton.y + 12, { 255, 255, 255, 255 });
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
        }

        SDL_RenderPresent(renderer);
        
        SDL_Delay(16); // Limit the loop to roughly 60 iterations per second.
    }


    // Release SDL resources in the reverse order of setup.
    TTF_CloseFont(buttonFont);
    TTF_CloseFont(overlayFont);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}