#include "Files/Files.h"
#include "Math/Vector.h"
#include <stdio.h>
#include <stdlib.h>





FILE *open_file(const char* name_file, const FILE_FLAGS flag) {

    const char *actions[4] = {"w", "r", "wr", "a"};
    FILE *file = fopen(name_file, actions[flag]);


    if (file == NULL) {
        fprintf(stdout, "[ERROR]: FILE %s NOT FOUND!!\n", name_file);
        exit(-1);
    }


    return file;
}




FILE *close_file(FILE *file) {

    if(file != NULL) {
        fclose(file);
        file = NULL;
    }

    return file;
}


void read_mesh_file(const char* name_file, Vec3 *mesh_data) {

    FILE *file = open_file(name_file, READ);
    unsigned int index = 0;
    while (fscanf(file, "%f, %f, %f", &mesh_data[index].x, &mesh_data[index].y, &mesh_data[index].z) != EOF) {
        index++;
    }    

    file = close_file(file);
}



unsigned int get_num_of_lines(const char* name_file) {
    
    FILE* file = open_file(name_file, READ);
    unsigned int result = 1;

    while (EOF != (fscanf(file, "%*[^\n]"), fscanf(file, "%*c"))) {
        result ++;
    }

	file = close_file(file);

    return result;
}
