//
// Created by Santiago Zamora on 30/10/22.
//

#include "Window/Window.h"
#include <SDL2/SDL.h>

struct Window *init_window(const char window_name[20]) {

  struct Window *window = malloc(sizeof(struct Window));
  if (window == NULL) {
	fprintf(stderr, "No hay suficiente memoria\n");
	exit(EXIT_FAILURE);
  }

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
	fprintf(stderr, "ERROR al inicializar SDL\n");
	exit(EXIT_FAILURE);
  }

  SDL_DisplayMode displayMode;
  SDL_GetCurrentDisplayMode(0, &displayMode);

  strcpy(window->window_name, window_name);

  window->ptr_sdl_window = SDL_CreateWindow(window->window_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
											displayMode.w, displayMode.h, SDL_WINDOW_BORDERLESS);

  if (window->ptr_sdl_window == NULL) {
	fprintf(stderr, "ERROR al inicializar la VENTANA de SDL\n");
	exit(EXIT_FAILURE);
  }

  SDL_SetWindowFullscreen(window->ptr_sdl_window, SDL_WINDOW_FULLSCREEN);
  return window;
}

void window_destroy(struct Window *window) {

  SDL_DestroyWindow(window->ptr_sdl_window);

  free(window);
  window = NULL;
}
