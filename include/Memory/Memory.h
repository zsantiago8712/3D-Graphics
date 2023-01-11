#ifndef MEMORY_H
#define MEMORY_H

#include "Math/Vector.h"
#include <Mesh/Mesh.h>


typedef enum {

    NORMAL_TYPE,
    STRUCT_TYPE,
    ARRAY_NDIMENSION_TYPE,

}MEM_TAG;




void init_memory_tracker(void);


void *alloc_memory(unsigned int size, MEM_TAG tag);
void *free_memory(void *memory_to_free, unsigned int size_allocated, MEM_TAG tag);


void **d2_array(unsigned int x, unsigned int y, unsigned int size_data);
void **free_2d_array(void** array);



void ***d3_array(unsigned int x,
				 unsigned int y,
				 unsigned int z,
				 unsigned int data_size);
void ***free_d3_array(void ***array);







#endif // !MEMORY_H
