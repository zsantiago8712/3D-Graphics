#ifndef MESH_H
#define MESH_H

#include "Math/Vector.h"

#define N_MESH_VERTICES 8
#define N_MESH_FACES 12



struct Triangle {
    Vec2 points[3];
};


struct Mesh{
   
    Vec3 *mesh_vertices;
    Vec3 *mesh_faces;

    unsigned int num_vertices;
    unsigned int num_faces;

    struct Triangle *traingle_to_render;
};




struct Mesh *get_mesh_from_file(const char* mesh_vertices_name_file, const char* mesh_faces_name_file);
struct Mesh* free_mesh(struct Mesh* mesh);


#endif // !MESH_H
#define MESH_H
