#ifndef MESH_H
#define MESH_H

#include "Math/Vector.h"



// TODO CAMBIAR TODO A FORMATO DOP - DOD



struct Triangles {
    Vec2 ***points;
};


struct Vertices {
    Vec3 **mesh_vertices;
    unsigned int *num_vertices;
    unsigned int num_max_vertices;
};


struct Faces {
    Vec3 **mesh_faces;
    unsigned int *num_faces;
    unsigned int num_max_faces;
};

struct Meshes {
    struct Vertices *vertices;
    struct Faces *faces;
    //struct Triangle **triangles;
    struct Triangles *triangles;
};



struct Meshes* init_mesh(unsigned int num_meshes, unsigned int num_vertices, unsigned int num_faces);
struct Meshes *free_meshes(struct Meshes *mesh, unsigned int num_meshes);





#endif // !MESH_H
#define MESH_H
