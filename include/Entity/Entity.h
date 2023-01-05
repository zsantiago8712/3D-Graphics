#ifndef ENTITY_H
#define ENTITY_H


#include "Mesh/Mesh.h"


struct Entity {

    struct Mesh *mesh;

};



struct Entity *set_entity(void);
struct Entity *free_entity(struct Entity *entity);

#endif // !DEBUG
