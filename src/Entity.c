#include "Entity/Entity.h"
#include <stdio.h>
#include <stdlib.h>

struct Entity *set_entity(void) {

  struct Entity *entity = malloc(sizeof(struct Entity));
  if (entity == NULL) {
    fprintf(stdout, "[ERROR]: NO HAY SUFICIENTE MEMORIA!!!");
    exit(EXIT_FAILURE);
  }

  entity->mesh =
      get_mesh_from_file("Meshes/Cube_vertices.txt", "Meshes/Cube_faces.txt");

  return entity;
}

struct Entity *free_entity(struct Entity *entity) {

    if(entity != NULL) {
        entity->mesh = free_mesh(entity->mesh);
        free(entity);
        entity = NULL;
    }

    return entity;
}
