#include "Files/Files.h"
#include "Math/Vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


FILE *open_file(const char *name_file, const FILE_FLAGS flag) {

  const char *actions[4] = {"w", "r", "wr", "a"};
  FILE *file = fopen(name_file, actions[flag]);

  if (file == NULL) {
    fprintf(stdout, "[ERROR]: FILE %s NOT FOUND!!\n", name_file);
    exit(-1);
  }

  return file;
}

FILE *close_file(FILE *file) {

  if (file != NULL) {
    fclose(file);
    file = NULL;
  }

  return file;
}


//  TODO SAVE TEXTURE AND NORMAL
void read_obj_file(const char *file_name, Vec3 *vertices, Vec3 *faces,
                   unsigned int *num_vertices, unsigned int *num_faces) {

  const char *types[5] = {"v ", "vt ", "vn ", "f "};

  float temp_arrray[6];
  FILE *file = open_file(file_name, READ);

  unsigned int index_vertices = 0;
  unsigned int index_faces = 0;
  char line[FILENAME_MAX];

  while (fgets(line, FILENAME_MAX, file)) {

    if (strncmp(line, types[VERTICES], 2) == 0) {

      sscanf(line, "v %f %f %f", &vertices[index_vertices].x,
             &vertices[index_vertices].y, &vertices[index_vertices].z);
      index_vertices++;

    } else if (strncmp(line, types[FACES], 2) == 0) {
      sscanf(line, "f %f/%f/%f %f/%f/%f %f/%f/%f",
             &faces[index_faces].x, &temp_arrray[0], &temp_arrray[1],
             &faces[index_faces].y, &temp_arrray[2], &temp_arrray[3],
             &faces[index_faces].z, &temp_arrray[4], &temp_arrray[5]);

      index_faces++;
    }
  }

  *num_vertices = index_vertices;
  *num_faces = index_faces;
  file = close_file(file);

}



Vec3* read_obj_file_test(const char *file_name, Vec3 *vertices, Vec3 *faces,
                   unsigned int *num_vertices, unsigned int *num_faces) {

  const char *types[5] = {"v ", "vt ", "vn ", "f "};

  float temp_arrray[6];
  FILE *file = open_file(file_name, READ);

  unsigned int index_vertices = 0;
  unsigned int index_faces = 0;
  char line[FILENAME_MAX];

  while (fgets(line, FILENAME_MAX, file)) {

    if (strncmp(line, types[VERTICES], 2) == 0) {

      sscanf(line, "v %f %f %f", &vertices[index_vertices].x,
             &vertices[index_vertices].y, &vertices[index_vertices].z);
      index_vertices++;

    } else if (strncmp(line, types[FACES], 2) == 0) {
      sscanf(line, "f %f/%f/%f %f/%f/%f %f/%f/%f",
             &faces[index_faces].x, &temp_arrray[0], &temp_arrray[1],
             &faces[index_faces].y, &temp_arrray[2], &temp_arrray[3],
             &faces[index_faces].z, &temp_arrray[4], &temp_arrray[5]);

      index_faces++;
    }
  }

  *num_vertices = index_vertices;
  *num_faces = index_faces;
  file = close_file(file);

  return vertices;
}






unsigned int get_num_of_types(const char *name_file, TYPES flag) {


    FILE *file = open_file(name_file, READ);
    const char *types[5] = {"v ", "vt ", "vn ", "f "};
    unsigned int result = 0;
    
    char line[FILENAME_MAX];
    while(fgets(line, FILENAME_MAX, file)) {
        if (strncmp(line, types[flag], 2) == 0) {
            result++;
        }
    }
  

  file = close_file(file);
  return result;
}




void read_mesh_file(const char *name_file, Vec3 *mesh_data) {

  FILE *file = open_file(name_file, READ);
  unsigned int index = 0;
  while (fscanf(file, "%f, %f, %f", &mesh_data[index].x, &mesh_data[index].y,
                &mesh_data[index].z) != EOF) {
    index++;
  }

  file = close_file(file);
}

unsigned int get_num_of_lines(const char *name_file) {

  FILE *file = open_file(name_file, READ);
  unsigned int result = 1;

  while (EOF != (fscanf(file, "%*[^\n]"), fscanf(file, "%*c"))) {
    result++;
  }

  file = close_file(file);

  return result;
}
