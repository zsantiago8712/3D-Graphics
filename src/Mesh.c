#include "Mesh/Mesh.h"
#include "Math/Vector.h"
#include "Files/Files.h"
#include "Memory/Memory.h"

static struct Vertices *init_vertices(unsigned int number_entities, unsigned int number_vertices);
static struct Faces *init_faces(unsigned int number_entities, unsigned int number_faces);
// static struct Triangle **init_triangles(unsigned int number_entities, unsigned int number_triangles);
static struct Triangles *init_triangles(unsigned int number_entities, unsigned int number_triangles);
static unsigned int get_num_of_max_types(const char **files_names, unsigned int num_entities, TYPES flag);

struct Meshes *init_mesh(const unsigned int num_meshes, const unsigned int num_vertices, const unsigned int num_faces) {

  struct Meshes *mesh = (struct Meshes *)alloc_memory(sizeof(struct Mesh), STRUCT_TYPE);
  mesh->vertices = init_vertices(num_meshes, num_vertices);
  mesh->faces = init_faces(num_meshes, num_faces);
  mesh->triangles = init_triangles(num_meshes, num_faces);

  return mesh;
}

struct Meshes *free_meshes(struct Meshes *mesh, const unsigned int num_meshes) {


  mesh->vertices->mesh_vertices = (Vec3 **) free_2d_array((void**) mesh->vertices->mesh_vertices);
  mesh->vertices->num_vertices = free_memory(mesh->vertices->num_vertices, sizeof(mesh->vertices->num_vertices), STRUCT_TYPE);
  mesh->vertices = free_memory(mesh->vertices, sizeof(struct Vertices), STRUCT_TYPE);

  mesh->triangles->points = (Vec2 ***) free_d3_array((void ***)mesh->triangles->points);
  mesh->triangles = free_memory(mesh->triangles, sizeof(struct Triangles), STRUCT_TYPE);

  mesh->faces->mesh_faces = (Vec3 **) free_2d_array((void **) mesh->faces->mesh_faces);
  mesh->faces->num_faces = free_memory(mesh->faces->num_faces, sizeof(mesh->faces->num_faces), STRUCT_TYPE);
  mesh->faces = free_memory(mesh->faces, sizeof(struct Faces), STRUCT_TYPE);

  mesh = (struct Meshes *)free_memory(mesh, sizeof(struct Meshes), STRUCT_TYPE);

  return mesh;
}

static struct Vertices *init_vertices(const unsigned int number_entities, const unsigned int number_vertices) {

  struct Vertices *vertices = (struct Vertices *)alloc_memory(sizeof(struct Vertices), STRUCT_TYPE);

  vertices->mesh_vertices = (Vec3**) d2_array(number_vertices, number_entities, sizeof(Vec3));
  // vertices->mesh_vertices = Vec3_Darray(number_vertices, number_entities);

//  vertices->mesh_vertices = (Vec3**)test(number_vertices, number_entities, sizeof(Vec3));
  vertices->num_vertices = (unsigned int *)alloc_memory(sizeof(unsigned int) * number_entities, STRUCT_TYPE);
  vertices->num_max_vertices = number_vertices;

  return vertices;
}

static struct Faces *init_faces(const unsigned int number_entities, const unsigned int number_faces) {

  struct Faces *faces = alloc_memory(sizeof(struct Faces), STRUCT_TYPE);
  faces->mesh_faces = (Vec3**) d2_array(number_faces, number_entities, sizeof(Vec3));
  // faces->mesh_faces = Vec3_Darray(number_faces, number_entities);
  faces->num_faces = (unsigned int *)alloc_memory(sizeof(int) * number_entities, STRUCT_TYPE);
  faces->num_max_faces = number_faces;

  return faces;
}

// TODO MAKE A 3D ARRAY
static struct Triangles *init_triangles(const unsigned int number_entities, const unsigned int number_triangles) {

  // struct Triangle **traingles = Triangle_Darray(number_entities, number_triangles);
  struct Triangles *triangles = alloc_memory(sizeof(struct Triangles), STRUCT_TYPE);
  triangles->points = (Vec2 ***) d3_array(number_triangles, number_entities, 3, sizeof(Vec2));

  return triangles;
}



struct Mesh *free_mesh(struct Mesh *mesh) {

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
