//
// Created by Santiago Zamora on 19/12/22.
//

#include "Math/Vector.h"
#include <math.h>
#include <stdio.h>

void print_vec3(const Vec3 vec) {
  printf("[%f, %f, %f]\n", vec.x, vec.y, vec.z);
}

Vec3 vec3_rotation_x(const Vec3 *vec, const float angle) {
  Vec3 res = {.x = vec->x,
              .y = vec->y * cosf(angle) - vec->z * sinf(angle),
              .z = vec->y * sinf(angle) + vec->z * cosf(angle)};

  return res;
}

Vec3 vec3_rotation_y(const Vec3 *vec, const float angle) {
  const Vec3 res = {.x = vec->x * cosf(angle) - vec->z * sinf(angle),
                    .y = vec->y,
                    .z = vec->x * sinf(angle) + vec->z * cosf(angle)};

  return res;
}

Vec3 vec3_rotation_z(const Vec3 *vec, const float angle) {
  const Vec3 res = {.x = vec->x * cosf(angle) - vec->y * sinf(angle),
                    .y = vec->x * sinf(angle) + vec->y * cosf(angle),
                    .z = vec->z};

  return res;
}

inline float vec2_magnitud(const Vec2 *vec) {
  return sqrtf((vec->x * vec->x) + (vec->y * vec->y));
}

inline float vec3_magnitud(const Vec3 *vec) {
  return sqrtf((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z));
}

Vec2 vec2_add(const Vec2 *vec, const Vec2 *vec2) {
  const Vec2 res = {.x = vec->x + vec2->x, .y = vec->y + vec2->y};

  return res;
}

Vec3 vec3_add(const Vec3 *vec, const Vec3 *vec2) {
  const Vec3 res = {
      .x = vec->x + vec2->x, .y = vec->y + vec2->y, .z = vec->z + vec2->z};

  return res;
}

Vec2 vec2_subs(const Vec2 *vec, const Vec2 *vec2) {
  const Vec2 res = {.x = vec->x - vec2->x, .y = vec->y - vec2->y};

  return res;
}

Vec3 vec3_subs(const Vec3 *vec, const Vec3 *vec2) {
  const Vec3 res = {
      .x = vec->x - vec2->x, .y = vec->y - vec2->y, .z = vec->z - vec2->z};

  return res;
}

Vec2 vec2_mult(const Vec2 *vec, const Vec2 *vec2) {
  const Vec2 res = {.x = vec->x * vec2->x, .y = vec->y * vec2->y};

  return res;
}

Vec3 vec3_mult(const Vec3 *vec, const Vec3 *vec2) {
  const Vec3 res = {
      .x = vec->x * vec2->x, .y = vec->y * vec2->y, .z = vec->z * vec2->z};

  return res;
}

Vec2 vec2_div(const Vec2 *vec, const Vec2 *vec2) {
  const Vec2 res = {.x = vec->x / vec2->x, .y = vec->y / vec2->y};

  return res;
}

Vec3 vec3_div(const Vec3 *vec, const Vec3 *vec2) {
  const Vec3 res = {
      .x = vec->x / vec2->x, .y = vec->y / vec2->y, .z = vec->z / vec2->z};

  return res;
}

Vec3 vec3_crossProduct(const Vec3 *vec, const Vec3 *vec2) {

  const Vec3 res = {.x = (vec->y * vec2->z) - (vec->z * vec2->y),
                    .y = (vec->z * vec2->x) - (vec->x * vec2->z),
                    .z = (vec->x * vec2->y) - (vec->y * vec2->x)};

  return res;
}


void vec3_normalize(Vec3 *vec) {
    const float magnitud = vec3_magnitud(vec);
    vec->x /= magnitud;
    vec->y /= magnitud;
    vec->z /= magnitud;

}




float vec2_dotProduct(const Vec2 *vec, const Vec2 *vec2) {
    const float res = (vec->x * vec2->x) + (vec->y * vec2->y);
    return res;
}

float vec3_dotProduct(const Vec3 *vec, const Vec3 *vec2) {
    const float res = (vec->x * vec2->x) + (vec->y * vec2->y) + (vec->z * vec2->z);
    return res;
}
