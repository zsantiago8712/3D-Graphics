#ifndef ENTITY_H
#define ENTITY_H


#include "Mesh/Mesh.h"


struct Entities {

    struct Meshes *mesh;
    unsigned int num_entites;
};



struct Entities *init_entities(const char** files_names, const unsigned int num_entities);
struct Entities *free_entities(struct Entities *entities);
void create_entities(const char** files_names, struct Entities* entities);


struct Entity {

    struct Mesh *mesh;

};



struct Entity *set_entity(void);
struct Entity *free_entity(struct Entity *entity);

#endif // !DEBUG
