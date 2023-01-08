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




Vec3 **Vec3_Darray(unsigned int size_j,
				   unsigned int size_i);


struct Triangle **Triangle_Darray(unsigned int size_j,
								   unsigned int size_i);


void *free_memory(void *memory_to_free, unsigned int size_allocated, MEM_TAG tag);


Vec3 **free_Vec3_Darray(Vec3 **array, unsigned int size_j, unsigned int size_i);

struct Triangle **free_Triangle_Darray(struct Triangle **array, unsigned int size_j, unsigned int size_i);



#endif // !MEMORY_H
