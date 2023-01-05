//
// Created by Santiago Zamora on 30/10/22.
//

#include "App/App.h"
#include "Camera/Camera.h"
#include "Entity/Entity.h"
#include "Math/Vector.h"
#include "Renderer/Renderer.h"

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#define FPS 60
#define FRAME_TARGET (1000 / FPS)

static bool process_input(struct App *app);
static void update(struct Entity *entity, struct Camera const *camera);

float angle_x = 0.0f;
float angle_y = 0.0f;
float angle_z = 0.0f;

/**
 * @brief Initialize app struct
 * @return app
 **/
void init_app(struct App *app) {
  app->window = init_window("3D-Graphics");
  app->renderer = init_render(app->window);
  app->camera = init_camara();
  app->entity = set_entity();
}

/**
 * @brief Destoy application
 * @param app - struct pointer App
 */
void app_destroy(struct App *app) {
  renderer_destroy(app->renderer);
  app->renderer = NULL;

  window_destroy(app->window);
  app->window = NULL;

  camara_destroy(app->camera);
  app->camera = NULL;

  app->entity = free_entity(app->entity);
}

/**
 * @brief Run application
 * @param struct App* - pointer of struct App
 * @return void
 **/
void app_run(struct App *app) {

  struct Cube cube;
  int window_height;
  int window_width;
  bool running = true;
  unsigned int time_to_wait = 0;

  SDL_GetWindowSize(app->window->ptr_sdl_window, &window_width, &window_height);

  while (running) {
    running = process_input(app);
    time_to_wait =
        FRAME_TARGET - (SDL_GetTicks64() - app->renderer->previous_frame_time);
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET) {
      SDL_Delay(time_to_wait);
    }
    app->renderer->previous_frame_time = SDL_GetTicks64();
    update(app->entity, app->camera);
    render(app->renderer, app->entity, window_width, window_height);
  }
}

static bool process_input(struct App *app) {

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

static void update(struct Entity *entity, struct Camera const *camera) {
    
    Vec3 mesh_face;
    Vec3 mesh_vertices[3];
    Vec3 transformed_vertex;
    Vec2 projected_points;

    angle_x += 0.01f;
    angle_y += 0.01f;
    angle_z += 0.01f;


    for (int i = 0; i < entity->mesh->num_faces; i++) {
        

        mesh_face = entity->mesh->mesh_faces[i];

        mesh_vertices[0] = entity->mesh->mesh_vertices[(int) mesh_face.x - 1];
        mesh_vertices[1] = entity->mesh->mesh_vertices[(int) mesh_face.y - 1];
        mesh_vertices[2] = entity->mesh->mesh_vertices[(int) mesh_face.z - 1];

        for (int j = 0; j < 3; j++) {
            transformed_vertex = vec3_rotation_x(&mesh_vertices[j], angle_x);
            transformed_vertex = vec3_rotation_y(&transformed_vertex, angle_y);
            transformed_vertex = vec3_rotation_z(&transformed_vertex, angle_z);

            projected_points = projection(transformed_vertex, camera->position.z, 640);
 
            entity->mesh->traingle_to_render[i].points[j] = projected_points;
        }
    }

 }
