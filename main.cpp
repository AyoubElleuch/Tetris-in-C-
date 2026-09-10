#include<stdio.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

using namespace std;

int main(){
    const int initResult = SDL_Init(SDL_INIT_VIDEO);
    if (initResult != 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }


    SDL_Quit();
    return 0;
}