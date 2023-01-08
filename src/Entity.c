#include "Entity/Entity.h"
#include <stdlib.h>
#include "Files/Files.h"
#include "Memory/Memory.h"
#include "Mesh/Mesh.h"


static unsigned int get_num_of_max_types(const char** files_names, unsigned int num_entities, TYPES flag);


struct Entities *init_entities(const char** files_names, const unsigned int num_entities) {

    struct Entities *entities = alloc_memory(sizeof(struct Entities), STRUCT_TYPE);

    const unsigned int num_max_vertices = get_num_of_max_types(files_names, num_entities, VERTICES);
    const unsigned int num_max_faces = get_num_of_max_types(files_names,num_entities, FACES);

    entities->num_entites = num_entities;
    entities->mesh = init_mesh(num_entities, num_max_vertices, num_max_faces);


    return entities;
}


void create_entities(const char** files_names, struct Entities* entities) {

  for(int i = 0; i < entities->num_entites; i++) {
	read_obj_file(files_names[i], entities->mesh->vertices->mesh_vertices[i],
				  entities->mesh->faces->mesh_faces[i],
				  &entities->mesh->vertices->num_vertices[i],
				  &entities->mesh->faces->num_faces[i]);


  }
}

struct Entities *free_entities(struct Entities *entities) {
    
    entities->mesh = free_meshes(entities->mesh, entities->num_entites);
    entities = free_memory((void*) entities, sizeof(struct Entities), STRUCT_TYPE);

    return entities;
}



static unsigned int get_num_of_max_types(const char** files_names, const unsigned int num_entities, TYPES flag) {

    unsigned int temp = 0;
    unsigned int num_types = 0;

    for(int i = 0; i < num_entities; i++) {
        temp = get_num_of_types(files_names[i], flag);

        if(temp > num_types) {
            num_types = temp;
        }

        temp = 0;
    }

    return num_types;
}


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
