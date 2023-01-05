//
// Created by Santiago Zamora on 30/10/22.
//

#ifndef INC_3D_GRAPHICS_RENDER_H
#define INC_3D_GRAPHICS_RENDER_H

#include "Window/Window.h"
#include "Entity/Entity.h"
#include <Math/Vector.h>


struct Renderer {

    SDL_Renderer *ptr_sdl_renderer;
    SDL_Texture *color_buffer_texture;
    unsigned int *color_buffer;
    unsigned int previous_frame_time;
};


struct Renderer *init_render(struct Window *window);

void renderer_destroy(struct Renderer *renderer);

void render_color_buffer(struct Renderer *renderer, int width);

void clear_color_buffer(struct Renderer *renderer, int width,
                        int height, unsigned int color);


void render(struct Renderer *renderer, struct Entity const *entity, const int width, const int height);


Vec2 projection (Vec3 position, float camara_z_position, float fov);

#endif // INC_3D_GRAPHICS_RENDER_H
