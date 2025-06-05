/*
 * Fullscreen Clock — A fullscreen digital clock for Linux
 * Copyright (C) 2025 Brian P. Giroux
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define FONT_PATH "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"
#define TIME_FONT_SIZE 400
#define DATE_FONT_SIZE 100

void render_text(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color colour, int x, int y, bool center, bool flip) {
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text, colour);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dst = { x, y, surface->w, surface->h };
    if (center) {
        dst.x -= surface->w / 2;
    }

    SDL_RendererFlip sdl_flip = flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer, texture, NULL, &dst, 0, NULL, sdl_flip);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("Fullscreen Clock",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0,
        SDL_WINDOW_FULLSCREEN_DESKTOP);

    SDL_SetWindowBordered(window, SDL_FALSE);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font* time_font = TTF_OpenFont(FONT_PATH, TIME_FONT_SIZE);
    TTF_Font* date_font = TTF_OpenFont(FONT_PATH, DATE_FONT_SIZE);

    if (!time_font || !date_font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return 1;
    }

    bool running = true;
    bool flip = false;
    SDL_Event e;

    SDL_Color time_colour = { 255, 255, 255, 255 };
    SDL_Color date_colour = { 100, 200, 255, 255 };

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q) running = false;
                if (e.key.keysym.sym == SDLK_SPACE) flip = !flip;
            }
        }

        time_t now = time(NULL);
        struct tm *local = localtime(&now);

        char time_str[6];
        strftime(time_str, sizeof(time_str), "%H:%M", local);

        char date_str[64];
        strftime(date_str, sizeof(date_str), "%A, %B %e", local);

        int w, h;
        SDL_GetRendererOutputSize(renderer, &w, &h);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        render_text(renderer, time_font, time_str, time_colour, w * 0.5, h * 0.05, true, flip);
        render_text(renderer, date_font, date_str, date_colour, w * 0.5, h * 0.65, true, flip);

        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
    }

    TTF_CloseFont(time_font);
    TTF_CloseFont(date_font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

