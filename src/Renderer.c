//
// Created by Santiago Zamora on 30/10/22.
//

#include "Renderer/Renderer.h"
#include "Window/Window.h"
#include <SDL2/SDL.h>


static SDL_Texture *create_color_buffer_texture(SDL_Renderer *renderer,
                                                int width, int height);

static unsigned int *create_color_buffer(int width, int height);


void render(struct Renderer *renderer, const int width, const int height) {

    SDL_SetRenderDrawColor(renderer->ptr_sdl_renderer, 0, 0, 0, 255);

    SDL_RenderClear(renderer->ptr_sdl_renderer);

    render_grid(renderer, width, height, 0X191919, 10);

    render_color_buffer(renderer, width);
    clear_color_buffer(renderer, width,
                       height, 0xFFFFF00);


    SDL_RenderPresent(renderer->ptr_sdl_renderer);
}


struct Renderer *init_render(struct Window *window) {

    int width;
    int height;
    struct Renderer *render = malloc(sizeof(struct Renderer));

    if (render == NULL) {
        fprintf(stderr, "ERROR al inicializar SDL\n");
        exit(EXIT_FAILURE);
    }


    SDL_GetWindowSize(window->ptr_sdl_window, &width, &height);
    render->ptr_sdl_renderer =
            SDL_CreateRenderer(window->ptr_sdl_window, -1, 0);

    if (render->ptr_sdl_renderer == NULL) {
        fprintf(stderr, "ERROR al inicializar el RENDERER de SLD\n");
        exit(EXIT_FAILURE);
    }

    render->color_buffer_texture =
            create_color_buffer_texture(render->ptr_sdl_renderer, width, height);
    render->color_buffer = create_color_buffer(width, height);

    return render;
}


/**
 * @brief Destroy SDL_Render and free memory
 * @params struct Renderer
 * */
void renderer_destroy(struct Renderer *renderer) {
    free(renderer->color_buffer);
    renderer->color_buffer = NULL;

    SDL_DestroyRenderer(renderer->ptr_sdl_renderer);

    free(renderer);
    renderer = NULL;
}

/**
 * @brief Change color from buffer
 * @params Render struct
 * @params const unsigned int width
 **/
void render_color_buffer(struct Renderer *renderer, const int width) {
    SDL_UpdateTexture(renderer->color_buffer_texture, NULL,
                      renderer->color_buffer,
                      (int) (width * sizeof(unsigned int)));

    SDL_RenderCopy(renderer->ptr_sdl_renderer, renderer->color_buffer_texture,
                   NULL, NULL);
}


void clear_color_buffer(struct Renderer *renderer, const int width,
                        const int height, const unsigned int color) {

    for (int y = 0; y < height; ++y) {

        for (int x = 0; x < width; ++x) {
            renderer->color_buffer[(width * y) + x] = color;
        }
    }
}



void render_grid(struct Renderer *render, const int width,
                 const int height, const unsigned int color, const unsigned int grid) {

    for (int y = 0; y < height; ++y) {

        for (int x = 0; x < width; x++) {

            if (x % grid == 0 || y % grid == 0) {
                render->color_buffer[(width * y) + x] = color;
            }
        }
    }
}


static unsigned int *create_color_buffer(const int width, const int height) {

    unsigned int *color_buffer =
            (unsigned int *) malloc(sizeof(unsigned int) * width * height);

    if (color_buffer == NULL) {
        fprintf(stderr, "ERROR no hay suficiente memoria!");
        exit(EXIT_FAILURE);
    }

    return color_buffer;
}



static SDL_Texture *create_color_buffer_texture(SDL_Renderer *renderer,
                                                const int width, const int height) {

    SDL_Texture *color_buffer_texture =
            SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                              SDL_TEXTUREACCESS_STREAMING, width, height);

    if (color_buffer_texture == NULL) {
        fprintf(stderr,
                "No se pudo crear la textura");
        exit(EXIT_FAILURE);
    }

    return color_buffer_texture;
}
