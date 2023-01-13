//
// Created by Santiago Zamora on 19/12/22.
//

#ifndef INC_3D_GRAPHICS_VECTOR_H
#define INC_3D_GRAPHICS_VECTOR_H

#include "sse2neon.h"

// Vector 2 dimensions
typedef union {

  float32x4_t values;

  union {
    struct {
      float x;
      float y;
    };

    struct {
      float r;
      float g;
    };

    struct {
      float s;
      float t;
    };
  };

} Vec2;

// Vector 3 dimensions
typedef union {

  float32x4_t values;
  union {
    struct {
      float x;
      float y;
      float z;
    };

    struct {
      float r;
      float g;
      float b;
    };

    struct {
      float s;
      float t;
      float a;
    };
  };

} Vec3;

void print_vec3(Vec3 vec);

Vec3 vec3_rotation_x(const Vec3 *vec, float angle);
Vec3 vec3_rotation_y(const Vec3 *vec, float angle);
Vec3 vec3_rotation_z(const Vec3 *vec, float angle);

float vec2_magnitud(const Vec2 *vec);
float vec3_magnitud(const Vec3 *vec);

// Suma de vectores
Vec2 vec2_add(const Vec2 *vec, const Vec2 *vec2);
Vec3 vec3_add(const Vec3 *vec, const Vec3 *vec2);

// Resta de vectores
Vec2 vec2_subs(const Vec2 *vec, const Vec2 *vec2);
Vec3 vec3_subs(const Vec3 *vec, const Vec3 *vec2);

// Multiplicacion de vectores
Vec2 vec2_mult(const Vec2 *vec, const Vec2 *vec2);
Vec3 vec3_mult(const Vec3 *vec, const Vec3 *vec2);

// Division de vectores
Vec2 vec2_div(const Vec2 *vec, const Vec2 *vec2);
Vec3 vec3_div(const Vec3 *vec, const Vec3 *vec2);

Vec3 vec3_crossProduct(const Vec3 *vec, const Vec3 *vec2);

void vec3_normalize(Vec3 *vec);

float vec2_dotProduct(const Vec2 *vec, const Vec2 *vec2);
float vec3_dotProduct(const Vec3 *vec, const Vec3 *vec2);

#endif // INC_3D_GRAPHICS_VECTOR_H
