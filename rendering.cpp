#include "rendering.h"

// AI wrote this function, did it better than me.
void drawText(
    SDL_Renderer* renderer,
    TTF_Font* font,
    const char* text,
    int centerX,
    int y,
    SDL_Color color) {
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text, color);
    if (!surface) {
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    const SDL_Rect destination = { centerX - surface->w / 2, y, surface->w, surface->h };
    SDL_FreeSurface(surface);

    if (texture) {
        SDL_RenderCopy(renderer, texture, nullptr, &destination);
        SDL_DestroyTexture(texture);
    }
}
