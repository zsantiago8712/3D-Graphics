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

static void update(struct Entities *entities, struct Camera const *camera,
                   const unsigned int window_width,
                   const unsigned int window_height);

const char *FILES_NAMES[100] = {"assets/cube.obj", "assets/cube2.obj"};

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
  app->entities = init_entities(FILES_NAMES, 2);
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

  app->entities = free_entities(app->entities);
}

/**
 * @brief Run application
 * @param struct App* - pointer of struct App
 * @return void
 **/
void app_run(struct App *app) {

  int window_height;
  int window_width;
  bool running = true;
  unsigned int time_to_wait = 0;

  create_entities(FILES_NAMES, app->entities);
  SDL_GetWindowSize(app->window->ptr_sdl_window, &window_width, &window_height);

  while (running) {
    running = process_input(app);
    time_to_wait =
        FRAME_TARGET - (SDL_GetTicks64() - app->renderer->previous_frame_time);
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET) {
      SDL_Delay(time_to_wait);
    }
    app->renderer->previous_frame_time = SDL_GetTicks();

    update(app->entities, app->camera, window_width, window_height);
    render(app->renderer, app->entities->mesh, window_width, window_height);
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

  return true;
}

static void update(struct Entities *entities, struct Camera const *camera,
                   const unsigned int window_width,
                   const unsigned int window_height) {

  Vec3 mesh_face;
  Vec3 mesh_vertices[3];
  Vec3 transformed_vertex[3];
  Vec2 projected_points;

  angle_x += 0.01f;
  angle_y += 0.01f;
  angle_z += 0.01f;
  entities->mesh->triangles->num_triangles = 0;
  for (int i = 0; i < entities->mesh->faces->num_faces[0]; i++) {

    mesh_face = entities->mesh->faces->mesh_faces[0][i];

    mesh_vertices[0] =
        entities->mesh->vertices->mesh_vertices[0][(int)mesh_face.x];
    mesh_vertices[1] =
        entities->mesh->vertices->mesh_vertices[0][(int)mesh_face.y];
    mesh_vertices[2] =
        entities->mesh->vertices->mesh_vertices[0][(int)mesh_face.z];

    // TRANSFORMACION
    for (int j = 0; j < 3; j++) {

      transformed_vertex[j] = vec3_rotation_x(&mesh_vertices[j], angle_x);
      transformed_vertex[j] = vec3_rotation_y(&transformed_vertex[j], angle_y);
      transformed_vertex[j] = vec3_rotation_z(&transformed_vertex[j], angle_z);

      transformed_vertex[j].z += 5;

      // transformed_vertex[j].z -= camera->position.z;
    }

    // TODO BACK FACE CULLING
    //  1) Find Vectors- (B-A) and (C-A)
    //  2) TAKE THERI CORSS PRODUCT AND FIND PERPENDICULAR NORMAL "N"
    Vec3 subs_res = vec3_subs(&transformed_vertex[1], &transformed_vertex[0]);
    Vec3 subs_res2 = vec3_subs(&transformed_vertex[2], &transformed_vertex[0]);
    Vec3 normal = vec3_crossProduct(&subs_res, &subs_res2);

    vec3_normalize(&subs_res);
    vec3_normalize(&subs_res2);
    vec3_normalize(&normal);

    // 3) Find the vector between the camera origin end the point "A"
    Vec3 camara_ray = vec3_subs(&camera->position, &transformed_vertex[0]);

    // 4) Calculate how alligned the camera ray is with the face normla using
    // dot product
    float normal_camara = vec3_dotProduct(&normal, &camara_ray);
    if (normal_camara > 0) {

      //  PROJECTION
      for (int k = 0; k < 3; k++) {

        projected_points = projection(transformed_vertex[k], 640);

        projected_points.x += ((float)window_width / 2);
        projected_points.y += ((float)window_height / 2);
        entities->mesh->triangles
            ->points[0][entities->mesh->triangles->num_triangles][k] =
            projected_points;
      }

      entities->mesh->triangles->num_triangles++;
    }
  }
}
