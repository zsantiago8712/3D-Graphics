#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600

SDL_Window *init_window(void);
SDL_Renderer *init_render(SDL_Window *window);

uint32_t *create_color_buffer(void);
void render(SDL_Renderer *renderer, SDL_Texture *color_buffer_texture,
            uint32_t *color_buffer);
void process_input(bool *is_running);
void destroy_window(uint32_t *color_buffer, SDL_Renderer *renderer,
                    SDL_Window *window);

void clear_color_buffer(uint32_t *color_buffer, const uint32_t color);
SDL_Texture *create_color_buffer_texture(SDL_Renderer *renderer);
void render_color_buffer(SDL_Texture *color_buffer_texture,
                         uint32_t *color_buffer, SDL_Renderer *renderer);

int main(int argc, char *argv[]) {

  SDL_Window *window = init_window();
  SDL_Renderer *renderer = init_render(window);
  SDL_Texture *color_buffer_texture = create_color_buffer_texture(renderer);
  bool is_running = true;
  uint32_t *color_buffer = create_color_buffer();

  while (is_running) {
    process_input(&is_running);
    render(renderer, color_buffer_texture, color_buffer);
  }

  destroy_window(color_buffer, renderer, window);
  return 0;
}

/*
 * @brief Inicializa la ventana
 * @param void
 * @return SDL_Window* window
 */
SDL_Window *init_window(void) {

  // Inicializa Todo DE SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "ERROR al inicializar SDL\n");
    exit(EXIT_FAILURE);
  }

  // Create SDL WINDOW
  SDL_Window *window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WIDTH, HEIGHT, SDL_WINDOW_BORDERLESS);

  if (window == NULL) {
    fprintf(stderr, "ERROR al inicializar la VENTANA de SDL\n");
    exit(EXIT_FAILURE);
  }

  return window;
}

/*
 * @brief Inicializa el renderer
 * @param SDL_Window* window
 * @return SDL_Renderer
 */
SDL_Renderer *init_render(SDL_Window *window) {

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

  if (renderer == NULL) {
    fprintf(stderr, "ERROR al inicializar el RENDERER de SLD\n");
    exit(EXIT_FAILURE);
  }

  return renderer;
}

uint32_t *create_color_buffer(void) {
  uint32_t *color_buffer = (uint32_t *)malloc(sizeof(uint32_t) * WIDTH * HEIGHT);;

  if (color_buffer == NULL) {

    fprintf(stderr, "ERROR no hay suficiente memoria!");
    exit(EXIT_FAILURE);
  }

  return color_buffer;
}

void destroy_window(uint32_t *color_buffer, SDL_Renderer *renderer,
                    SDL_Window *window) {

  free(color_buffer);
  color_buffer = NULL;

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

/*
 * @brief Procesa los inputs
 * @param bool is_running
 * @return void
 */
void process_input(bool *is_running) {

  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {

  case SDL_QUIT:
    *is_running = false;
    break;

  case SDL_KEYDOWN:
    if (event.key.keysym.sym == SDLK_ESCAPE) {
      *is_running = false;
    }
    break;

  default:
    break;
  }
}

void update() {}

/*
 * @brief Renderiza, limpia y actuliza la ventana
 * @param SDL_Renderer *renderer
 * @return void
 */
void render(SDL_Renderer *renderer, SDL_Texture *color_buffer_texture,
            uint32_t *color_buffer) {

  // Pone el color y la transparencia del background de la ventana
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  // Limpia la ventana
  SDL_RenderClear(renderer);

  render_color_buffer(color_buffer_texture, color_buffer, renderer);
  clear_color_buffer(color_buffer, 0xFFFFF00);

  // Actuliza la ventana
  SDL_RenderPresent(renderer);
}

void clear_color_buffer(uint32_t *color_buffer, const uint32_t color) {

  for (int y = 0; y < HEIGHT; y++) {

    for (int x = 0; x < WIDTH; x++) {

      color_buffer[(WIDTH * y) + x] = color;
    }
  }

  // memset((void *)color_buffer, color, (int)sizeof(color_buffer));
}

SDL_Texture *create_color_buffer_texture(SDL_Renderer *renderer) {

  SDL_Texture *color_buffer_texture = NULL;
  color_buffer_texture =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                        SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

  if (color_buffer_texture == NULL) {
    fprintf(stderr, "No se pudo crear la textura");
    exit(EXIT_FAILURE);
  }

  return color_buffer_texture;
}

void render_color_buffer(SDL_Texture *color_buffer_texture,
                         uint32_t *color_buffer, SDL_Renderer *renderer) {

  SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer,
                    (int) (WIDTH * sizeof(uint32_t)));

  SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}
