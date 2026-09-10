#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void drawText(
    SDL_Renderer* renderer,
    TTF_Font* font,
    const char* text,
    int centerX,
    int y,
    SDL_Color color);
