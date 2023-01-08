//
// Created by Santiago Zamora on 19/12/22.
//

#include "Math/Vector.h"
#include <math.h>
#include <stdio.h>

static void changeValues(Vec3 *vec, const float x, const float y, const float z) {
  vec->x = x;
  vec->y = y;
  vec->z = z;
}







void print_vec3(const Vec3 vec) {
    printf("[%f, %f, %f]\n", vec.x, vec.y, vec.z);
}




Vec3 vec3_rotation_x(const Vec3 *vec, const float angle) {
  Vec3 res = {
	  .x = vec->x,
	  .y = vec->y * cosf(angle) - vec->z * sinf(angle),
	  .z = vec->y * sinf(angle) + vec->z * cosf(angle)
  };

  return res;
}




Vec3 vec3_rotation_y(const Vec3 *vec, const float angle) {
  const Vec3 res = {
	  .x = vec->x * cosf(angle) - vec->z * sinf(angle),
	  .y = vec->y,
	  .z = vec->x * sinf(angle) + vec->z * cosf(angle)
  };

  return res;
}



Vec3 vec3_rotation_z(const Vec3 *vec, const float angle) {
  const Vec3 res = {
	  .x = vec->x * cosf(angle) - vec->y * sinf(angle),
	  .y = vec->x * sinf(angle) + vec->y * cosf(angle),
	  .z = vec->z
  };

  return res;
}
