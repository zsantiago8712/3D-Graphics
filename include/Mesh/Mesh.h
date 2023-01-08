#ifndef MESH_H
#define MESH_H

#include "Math/Vector.h"



// TODO CAMBIAR TODO A FORMATO DOP - DOD




struct Triangle {
    Vec2 points[3];
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
    struct Triangle **triangles;
};



struct Meshes* init_mesh(unsigned int num_meshes, unsigned int num_vertices, unsigned int num_faces);
struct Meshes *free_meshes(struct Meshes *mesh, unsigned int num_meshes);





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
