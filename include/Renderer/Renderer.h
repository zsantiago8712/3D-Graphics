//
// Created by Santiago Zamora on 30/10/22.
//

#ifndef INC_3D_GRAPHICS_RENDER_H
#define INC_3D_GRAPHICS_RENDER_H

#include "Window/Window.h"
#include <SDL2/SDL.h>

struct Renderer {

    SDL_Renderer *ptr_sdl_renderer;
    SDL_Texture *color_buffer_texture;
    unsigned int *color_buffer;
};


struct Renderer *init_render(struct Window *window);

void renderer_destroy(struct Renderer *renderer);

void render_color_buffer(struct Renderer *renderer, int width);

void clear_color_buffer(struct Renderer *renderer, int width,
                        int height, unsigned int color);

void render_grid(struct Renderer *render, int width,
                 int height, unsigned int color, unsigned int grid);


void render(struct Renderer *renderer, const int width, const int height);


#endif // INC_3D_GRAPHICS_RENDER_H
