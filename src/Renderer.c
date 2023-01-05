//
// Created by Santiago Zamora on 30/10/22.
//

#include "Renderer/Renderer.h"
#include "Math/Vector.h"
#include "Window/Window.h"
#include <SDL2/SDL.h>

/**
 *
 * @NOTE: SDL maneja su sisteam de cordenadas de arriba hacia abajo
 */
static SDL_Texture *create_color_buffer_texture(SDL_Renderer *renderer,
                                                int width, int height);

static unsigned int *create_color_buffer(int width, int height);

static void draw_rectangle(struct Renderer *renderer, int window_width,
                           int window_height, int width, int height,
                           int x_rectangle, int y_rectangle,
                           unsigned int color);

static void draw_pixel(unsigned int *color_buffer, int window_width,
                       int window_height, int x, int y, unsigned int color);

static void render_grid(struct Renderer *renderer, int width, int height,
                        unsigned int color, unsigned int grid);

void render(struct Renderer *renderer, struct Entity const *entity,
            const int width, const int height) {


  int x_rectangle;
  int y_rectangle;

  SDL_SetRenderDrawColor(renderer->ptr_sdl_renderer, 0, 0, 0, 255);

  SDL_RenderClear(renderer->ptr_sdl_renderer);

  for (int i = 0; i < entity->mesh->num_faces; i++) {

	x_rectangle = (int) (entity->mesh->traingle_to_render[i].points[0].x + (float) width / 2);
	y_rectangle = (int)(entity->mesh->traingle_to_render[i].points[0].y + (float) height / 2);

    draw_rectangle(renderer, width, height, 3, 3, x_rectangle,
                   y_rectangle,0XFFFF00);

	x_rectangle = (int) (entity->mesh->traingle_to_render[i].points[1].x + (float) width / 2);
	y_rectangle = (int)(entity->mesh->traingle_to_render[i].points[1].y + (float) height / 2);
	draw_rectangle(renderer, width, height, 3, 3, x_rectangle,
				   y_rectangle,0XFFFF00);

	x_rectangle = (int) (entity->mesh->traingle_to_render[i].points[2].x + (float) width / 2);
	y_rectangle = (int)(entity->mesh->traingle_to_render[i].points[2].y + (float) height / 2);
	draw_rectangle(renderer, width, height, 3, 3, x_rectangle,
				   y_rectangle,0XFFFF00);
  }


  render_grid(renderer, width, height, 0xFFFFFF, 10);
  render_color_buffer(renderer, width);
  clear_color_buffer(renderer, width, height, 0x000000);

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
  render->ptr_sdl_renderer = SDL_CreateRenderer(window->ptr_sdl_window, -1, 0);

  if (render->ptr_sdl_renderer == NULL) {
    fprintf(stderr, "ERROR al inicializar el RENDERER de SLD\n");
    exit(EXIT_FAILURE);
  }

  render->color_buffer_texture =
      create_color_buffer_texture(render->ptr_sdl_renderer, width, height);
  render->color_buffer = create_color_buffer(width, height);

  render->previous_frame_time = 0;

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
 * @params Renderer struct
 * @params const unsigned int width
 **/
void render_color_buffer(struct Renderer *renderer, const int width) {
  SDL_UpdateTexture(renderer->color_buffer_texture, NULL,
                    renderer->color_buffer,
                    (int)(width * sizeof(unsigned int)));

  SDL_RenderCopy(renderer->ptr_sdl_renderer, renderer->color_buffer_texture,
                 NULL, NULL);
}

/**
 * @brief Clear my window with the color entered
 * @param renderer - Render struct
 * @param width - WIndow width
 * @param height - Window height
 * @param color - Color in hexadecimal format
 */
void clear_color_buffer(struct Renderer *renderer, const int width,
                        const int height, const unsigned int color) {

  for (int y = 0; y < height; ++y) {

    for (int x = 0; x < width; ++x) {
      draw_pixel(renderer->color_buffer, width, height, x, y, color);
    }
  }
}

static void render_grid(struct Renderer *renderer, const int width,
                        const int height, const unsigned int color,
                        const unsigned int grid) {
  for (int y = 0; y < height; y += 20) {

    for (int x = 0; x < width; x += 20) {
      draw_pixel(renderer->color_buffer, width, height, x, y, color);
    }
  }
}

static void draw_rectangle(struct Renderer *renderer, const int window_width,
                           const int window_height, const int width,
                           const int height, const int x_rectangle,
                           const int y_rectangle, const unsigned int color) {

  for (int y = y_rectangle; y < (y_rectangle + height); y++) {

    for (int x = x_rectangle; x < (width + x_rectangle); x++) {

      draw_pixel(renderer->color_buffer, window_width, window_height, x, y,
                 color);
    }
  }
}

static unsigned int *create_color_buffer(const int width, const int height) {

  unsigned int *color_buffer =
      (unsigned int *)malloc(sizeof(unsigned int) * width * height);

  if (color_buffer == NULL) {
    fprintf(stderr, "ERROR no hay suficiente memoria!");
    exit(EXIT_FAILURE);
  }

  return color_buffer;
}

static SDL_Texture *create_color_buffer_texture(SDL_Renderer *renderer,
                                                const int width,
                                                const int height) {

  SDL_Texture *color_buffer_texture =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                        SDL_TEXTUREACCESS_STREAMING, width, height);

  if (color_buffer_texture == NULL) {
    fprintf(stderr, "No se pudo crear la textura");
    exit(EXIT_FAILURE);
  }

  return color_buffer_texture;
}

static void draw_pixel(unsigned int *color_buffer, const int window_width,
                       const int window_height, const int x, const int y,
                       const unsigned int color) {

  if ((x < window_width && x >= 0) && (y < window_height && y >= 0)) {
    color_buffer[(window_width * y) + x] = color;
  }
}

Vec2 projection(const Vec3 position, const float camara_z_position,
                const float fov) {
  Vec2 point = {(position.x * fov) / (position.z - camara_z_position),
                (position.y * fov) / (position.z - camara_z_position)};

  return point;
}
