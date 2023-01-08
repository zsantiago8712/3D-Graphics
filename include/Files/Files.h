#ifndef FILE_H
#define FILE_H

#include "Math/Vector.h"
#include <stdio.h>


typedef enum {

  VERTICES = 0,
  VT = 1,
  VN = 2,
  FACES = 3,

} TYPES;



typedef enum {

    WRITE = 0,
    READ = 1,
    WRITE_AND_READ = 2,
    
}FILE_FLAGS;


// TODO TEST
void test(const char *file_name, Vec3 **vertices, Vec3 **faces,
		  unsigned int *num_vertices, unsigned int *num_faces);

FILE *open_file(const char* name_file, const FILE_FLAGS flag);

FILE *close_file(FILE *file);

unsigned int get_num_of_types(const char *name_file, TYPES flag);


unsigned int get_num_of_lines(const char* name_file);
void read_obj_file(const char *file_name, Vec3 *vertices, Vec3 *faces, unsigned int* num_vertices, unsigned int* num_faces);


void read_mesh_file(const char* name_file, Vec3 *mesh_data);



#endif // !FILE_H
