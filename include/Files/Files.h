#ifndef FILE_H
#define FILE_H

#include "Math/Vector.h"
#include <stdio.h>



typedef enum {

    WRITE = 0,
    READ = 1,
    WRITE_AND_READ = 2,
    
}FILE_FLAGS;


FILE *open_file(const char* name_file, const FILE_FLAGS flag);

FILE *close_file(FILE *file);



unsigned int get_num_of_lines(const char* name_file);

void read_mesh_file(const char* name_file, Vec3 *mesh_data);



#endif // !FILE_H
