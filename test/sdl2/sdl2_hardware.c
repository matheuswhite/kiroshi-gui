/**
 * @file sdl2_hardware.c
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief
 * @version 0.1
 * @date 28/04/2022
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "kiroshi/hardware.h"
#include <SDL.h>

static SDL_Window *window;
static SDL_Renderer *renderer;

int krs_hardware_init()
{
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("kiroshi-gui", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    return 0;
}

void krs_hardware_reset()
{
    SDL_DestroyWindow(window);
    SDL_Quit();

    krs_hardware_init();
}

void krs_hardware_refresh(uint16_t *vram, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    krs_hardware_refresh_all(vram);
}

void krs_hardware_refresh_all(uint16_t *vram)
{
    uint8_t r, g, b;
    uint16_t pixel;

    for (int i = 0; i < SCREEN_WIDTH; ++i) {
        for (int j = 0; j < SCREEN_HEIGHT; ++j) {
            pixel = vram[j * SCREEN_WIDTH + i];
            r     = ((pixel & 0x7C00) >> 10) * 255.0 / 7.0;
            b     = ((pixel & 0x03E0) >> 5) * 255.0 / 7.0;
            g     = (pixel & 0x1F) * 255.0 / 7.0;
            SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            SDL_RenderDrawPoint(renderer, i, j);
        }
    }
    SDL_RenderPresent(renderer);
}

void krs_hardware_sleep_ms(uint32_t ms)
{
    SDL_Delay(ms);
}
