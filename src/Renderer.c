//
// Created by Santiago Zamora on 30/10/22.
//

#include "Renderer/Renderer.h"
#include "Entity/Entity.h"
#include "Math/Vector.h"
#include "Window/Window.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <stdlib.h>

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

static void draw_line(unsigned int *color_buffer, const int window_width,
                      const int window_height, const unsigned int x0,
                      const unsigned int y0, const unsigned int x1,
                      const unsigned int y1, const unsigned int color);

static void draw_triangle(unsigned int *color_buffer, const int window_width,
                          const int window_height, const unsigned int x0,
                          const unsigned int y0, const unsigned x1,
                          const unsigned y1, const unsigned int x2,
                          const unsigned y2, const unsigned color);




void render(struct Renderer *renderer, struct Entities const *entities,
            const int width, const int height) {

  int x_rectangle;
  int y_rectangle;

  SDL_SetRenderDrawColor(renderer->ptr_sdl_renderer, 0, 0, 0, 255);

  SDL_RenderClear(renderer->ptr_sdl_renderer);

  for (int i = 0; i < entities->mesh->faces->num_faces[0]; i++) {

    draw_rectangle(renderer, width, height, 3, 3,
                   entities->mesh->triangles[0][i].points[0].x,
                   entities->mesh->triangles[0][i].points[0].y, 0XFF0000);

    draw_rectangle(renderer, width, height, 3, 3,
                   entities->mesh->triangles[0][i].points[1].x,
                   entities->mesh->triangles[0][i].points[1].y, 0XFF0000);

    draw_rectangle(renderer, width, height, 3, 3,
                   entities->mesh->triangles[0][i].points[2].x,
                   entities->mesh->triangles[0][i].points[2].y, 0XFF0000);

    draw_triangle(renderer->color_buffer, width, height,
                  entities->mesh->triangles[0][i].points[0].x,
                  entities->mesh->triangles[0][i].points[0].y,
                  entities->mesh->triangles[0][i].points[1].x,
                  entities->mesh->triangles[0][i].points[1].y,
                  entities->mesh->triangles[0][i].points[2].x,
                  entities->mesh->triangles[0][i].points[2].y, 0x296E01);
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

static void draw_triangle(unsigned int *color_buffer, const int window_width,
                          const int window_height, const unsigned int x0,
                          const unsigned int y0, const unsigned x1,
                          const unsigned y1, const unsigned int x2,
                          const unsigned y2, const unsigned color) {

  draw_line(color_buffer, window_width, window_height, x0, y0, x1, y1, color);
  draw_line(color_buffer, window_width, window_height, x1, y1, x2, y2, color);
  draw_line(color_buffer, window_width, window_height, x2, y2, x0, y0, color);
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

static void draw_line(unsigned int *color_buffer, const int window_width,
                      const int window_height, const unsigned int x0,
                      const unsigned int y0, const unsigned int x1,
                      const unsigned int y1, const unsigned int color) {

  const int delta_x = (x1 - x0);
  const int delta_y = (y1 - y0);

  const unsigned int lenght_side =
      (abs(delta_x) >= abs(delta_y)) ? abs(delta_x) : abs(delta_y);

  const float x_inc = delta_x / (float)lenght_side;
  const float y_inc = delta_y / (float)lenght_side;

  float current_x = (float)x0;
  float current_y = (float)y0;

  for (int i = 0; i <= lenght_side; i++) {
    draw_pixel(color_buffer, window_width, window_height, roundf(current_x),
               roundf(current_y), color);
    current_x += x_inc;
    current_y += y_inc;
  }
}

Vec2 projection(const Vec3 position, const float camara_z_position,
                const float fov) {
    
    // Projection orotgonal, es como vemos las cosas 
  Vec2 point = {(position.x * fov) / (position.z - camara_z_position),
                (position.y * fov) / (position.z - camara_z_position)};

  
   // Projection ortografica: No importa que tanl lejos este todo, todo es del mismo tamaño
  // Vec2 point = {(position.x * 128),
  //               (position.y * 128)};
  // 


  return point;
}
