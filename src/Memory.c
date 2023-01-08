#include "Memory/Memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <Math/Vector.h>

struct Memory_Tracker {

  unsigned int total_size_of_memory_allocated;
  unsigned int size_of_memory_allocated[10];
};

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






Vec3 **Vec3_Darray(const unsigned int size_j,
				   const unsigned int size_i) {

  Vec3 *mem = (Vec3 *)alloc_memory(size_j * size_i * sizeof(Vec3), ARRAY_NDIMENSION_TYPE);
  Vec3 **array = (Vec3 **)alloc_memory(size_i * sizeof(Vec3 *), ARRAY_NDIMENSION_TYPE);

  for (int i = 0; i < size_i; i++) {
	array[i] = mem + i * size_j;
  }

  return array;
}

struct Triangle **Triangle_Darray(const unsigned int size_j,
								  const unsigned int size_i) {

  struct Triangle *mem = (struct Triangle *)alloc_memory(size_j * size_i * sizeof(struct Triangle), ARRAY_NDIMENSION_TYPE);
  struct Triangle **array = (struct Triangle **)alloc_memory(size_i * sizeof(struct Triangle *), ARRAY_NDIMENSION_TYPE);

  for (int i = 0; i < size_i; i++) {
	array[i] = mem + i * size_j;
  }

  return array;
}

/**
 * @brief Free/Destroy 2D Array
 * @param array - Array of any type
 * @param size_j - Number of Columns
 * @param size_i - Number of Rows
 * @param size_type - Size of type variable of the array
 * @return array - Array free
 **/
Vec3 **free_Vec3_Darray(Vec3 **array, const unsigned int size_j, const unsigned int size_i) {

  assert(size_j > 0 && size_i > 0);
  if (array == NULL) {
	fprintf(stderr, "[WARNING] TRYING TO FREE A MEMORY HAS BEEN FREE\n");
	return array;
  }

  array[0] = free_memory(array[0], (size_j * size_i * sizeof(Vec3)), ARRAY_NDIMENSION_TYPE);
  for (int i = 1; i < size_j; i++) {
	array[i] = NULL;
  }

  array = free_memory(array, (sizeof(array) * size_i), ARRAY_NDIMENSION_TYPE);

  return array;
}

struct Triangle **free_Triangle_Darray(struct Triangle **array, const unsigned int size_j, const unsigned int size_i) {

  assert(size_j > 0 && size_i > 0);
  if (array == NULL) {
	fprintf(stderr, "[WARNING] TRYING TO FREE A MEMORY HAS BEEN FREE\n");
	return array;
  }

  array[0] = free_memory(array[0], (size_j * size_i * sizeof(struct Triangle)), ARRAY_NDIMENSION_TYPE);
  for (int i = 1; i < size_j; i++) {
	array[i] = NULL;
  }

  array = free_memory(array, (sizeof(array) * size_i), ARRAY_NDIMENSION_TYPE);

  return array;
}