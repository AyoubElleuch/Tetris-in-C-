#include<stdio.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

using namespace std;



int main(){
    const int width = 10, height = 20, cell_size = 30;
    const int window_width = 800, window_height = 600;
    
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

    while(running){
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
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