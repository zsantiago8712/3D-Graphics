#include "Mesh/Mesh.h"
#include "Math/Vector.h"
#include "Files/Files.h"
#include <stdio.h>
#include <stdlib.h>


struct Mesh *get_mesh_from_file(const char* mesh_vertices_name_file, const char* mesh_faces_name_file) {
 

    struct Mesh *mesh = malloc(sizeof(struct Mesh));

    mesh->num_vertices = get_num_of_lines(mesh_vertices_name_file);
    mesh->num_faces = get_num_of_lines(mesh_faces_name_file);


    mesh->mesh_vertices = malloc(sizeof(Vec3) * mesh->num_vertices);
    if (mesh->mesh_vertices == NULL) {
        fprintf(stdout, "[ERROR]: NO HAY SUFICIENTE MEMORIA!!!");
        exit(EXIT_FAILURE);
    }


    mesh->mesh_faces = malloc(sizeof(Vec3) * mesh->num_faces);
    if (mesh->mesh_faces == NULL) {
        fprintf(stdout, "[ERROR]: NO HAY SUFICIENTE MEMORIA!!!");
        exit(EXIT_FAILURE);
    }
    
    mesh->traingle_to_render = malloc(sizeof(struct Triangle) * mesh->num_faces);
    if (mesh->traingle_to_render == NULL) {
        fprintf(stdout, "[ERROR]: NO HAY SUFICIENTE MEMORIA!!!");
        exit(EXIT_FAILURE);
    }

    read_mesh_file(mesh_vertices_name_file, mesh->mesh_vertices);
    read_mesh_file(mesh_faces_name_file, mesh->mesh_faces);
    
    return mesh;
}




struct Mesh* free_mesh(struct Mesh* mesh) {
 
    if (mesh->mesh_vertices != NULL) {
        free(mesh->mesh_vertices);
        mesh->mesh_vertices = NULL;
    }

    if (mesh->mesh_faces != NULL) {
        free(mesh->mesh_faces);
        mesh->mesh_faces = NULL;
    }

	free(mesh);
	mesh = NULL;

	return mesh;
}
