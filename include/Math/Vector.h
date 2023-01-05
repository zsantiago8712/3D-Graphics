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

}Vec2;


//Vector 3 dimensions
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

}Vec3;


struct Cube {
    Vec3 points[729];
    Vec2 projected_points[729];
};



void create_cube (struct Cube *cube);



void print_vec3(const Vec3 vec);

Vec3 vec3_rotation_x(const Vec3 *vec, const float angle);
Vec3 vec3_rotation_y(const Vec3 *vec, const float angle);
Vec3 vec3_rotation_z(const Vec3 *vec, const float angle);

#endif //INC_3D_GRAPHICS_VECTOR_H


