#include<stdio.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

using namespace std;

int main(){
    // Start the SDL video subsystem before creating any windows.
    const int initResult = SDL_Init(SDL_INIT_VIDEO);
    if (initResult != 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create the initial play area; rendering will be added later.
    SDL_Window* window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

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
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Limit the loop to roughly 60 iterations per second.
    }


    // Release SDL resources in the reverse order of setup.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}