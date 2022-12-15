//
// Created by Santiago Zamora on 30/10/22.
//

#include "App/App.h"
#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdbool.h>


static bool process_input(struct App *app);


/**
 * @brief Initialize app strict
 * @return app
 **/

void init_app (struct App *app)
{
    app->window = init_window("3D-Graphics");
    app->renderer = init_render(app->window);
}

void app_destroy(struct App *app)
{
  renderer_destroy(app->renderer);
  app->renderer = NULL;

  window_destroy(app->window);
  app->window = NULL;
}

void app_run(struct App *app)
{

    int window_height;
    int window_width;

    SDL_GetWindowSize(app->window->ptr_sdl_window, &window_width, &window_height);
    bool running = true;
    while (running) {
        running = process_input(app);
        render(app->renderer, window_width, window_height);
    }
}


static bool process_input(struct App *app)
{

  SDL_PollEvent(&app->event);

  switch (app->event.type) {
  case SDL_QUIT:
    return false;

  case SDL_KEYDOWN:
    if (app->event.key.keysym.sym == SDLK_ESCAPE) {
      return false;
    }
    return true;

  default:
    return true;
  }
}

// static void update(App app) {}
