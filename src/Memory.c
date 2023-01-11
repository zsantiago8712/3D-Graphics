#include "Memory/Memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <Math/Vector.h>

struct Memory_Tracker {

  unsigned int total_size_of_memory_allocated;
  unsigned int size_of_memory_allocated[10];
};

void *malloc1d(size_t dim1_data_size) {
  void *ptr = malloc(dim1_data_size);
#if !defined(NDEBUG)
  if (ptr == NULL && dim1_data_size != 0)
	fprintf(stderr, "Error: 'malloc1d' failed to allocate %zu bytes.\n", dim1_data_size);
#endif
  return ptr;
}

void **malloc2d(size_t dim1, size_t dim2, size_t data_size) {
  size_t i, stride;
  void **ptr;
  unsigned char *p2;
  stride = dim2 * data_size;
  ptr = malloc1d(dim1 * sizeof(void *) + dim1 * stride);
  p2 = (unsigned char *)(ptr + dim1);
  for (i = 0; i < dim1; i++)
	ptr[i] = &p2[i * stride];
  return ptr;
}

static struct Memory_Tracker memory_tracker;

/**
 * @brief initializaded memory tracker
 **/
void init_memory_tracker(void) {

  memory_tracker.total_size_of_memory_allocated = 0;
  for (int i = 0; i < 10; i++) {
	memory_tracker.size_of_memory_allocated[i] = 0;
  }
}

/**
 * @brief Memory allocator
 * @param size - Size of the meory you want to allocated
 * @return void* - Mmoery allocated
 */
void *alloc_memory(const unsigned int size, const MEM_TAG tag) {

  assert(size > 0);
  void *memory_alloc = malloc(size);
  if (memory_alloc == NULL) {
	fprintf(stderr, "[ERROR]: NO HAY MEMORIA SUFICIENTE\n");
	exit(EXIT_FAILURE);
  }

  memory_tracker.total_size_of_memory_allocated += size;
  memory_tracker.size_of_memory_allocated[tag] += size;

  return memory_alloc;
}

/**
 * @brief Free mememory allocated
 * @param memory_to_free - Memory you want to free
 * @return void* - Memory freed
 **/
void *free_memory(void *memory_to_free, const unsigned int size_allocated, const MEM_TAG tag) {

  assert(size_allocated > 0);
  if (memory_to_free == NULL) {
	fprintf(stderr, "[WARNING] TRYING TO FREE A MOMERY HAS BEEN FREE\n");
	return memory_to_free;
  }

  memory_tracker.total_size_of_memory_allocated -= size_allocated;
  memory_tracker.size_of_memory_allocated[tag] -= size_allocated;

  free(memory_to_free);
  memory_to_free = NULL;

  return memory_to_free;
}

/**
 * @brief Alloc memory for 2D OR MORE DIMENSIONS CAHCE FRIENDLY
 * @param size_type - Size of the varible type you want your array
 * @param size_x - Number of Columns
 * @param size_y - Number of Rows
 * @return void* - Array allocated
 **/





void **d2_array(const unsigned int x, const unsigned int y, const unsigned int size_data) {

  const unsigned int stride = x * size_data;
  void **array = (void **)alloc_memory(y * sizeof(void *) + x * stride, ARRAY_NDIMENSION_TYPE);
  unsigned char *mem = (unsigned char *)(array + y);

  for (unsigned int i = 0; i < y; i++) {
	array[i] = &mem[i * stride];
  }

  return array;
}

void **free_2d_array(void **array) {

  free(array);
  array = NULL;

  return array;
}

void ***d3_array(const unsigned int x,
				 const unsigned int y,
				 const unsigned int z,
				 const unsigned int data_size) {

  const unsigned int stride = x * z * data_size;
  const unsigned int stride2 = z * data_size;

  void ***array =
	  alloc_memory(y * sizeof(void **) + y * x * sizeof(void *) + y * stride, ARRAY_NDIMENSION_TYPE);
  void **ptr = (void **)(array + y);

  unsigned char *mem = (unsigned char *)(ptr + y * x);

  for (unsigned int i = 0; i < y; i++) {
	array[i] = &ptr[i * x];

	for (unsigned int j = 0; j < x; j++) {
	  ptr[i * x + j] = &mem[i * stride + stride2 * j];
	}
  }

  return array;
}

void ***free_d3_array(void ***array) {

  free(array);
  array = NULL;

  return array;
}

