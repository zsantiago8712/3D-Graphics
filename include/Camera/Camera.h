//
// Created by Santiago Zamora on 20/12/22.
//

#ifndef INC_3D_GRAPHICS_CAMERA_H
#define INC_3D_GRAPHICS_CAMERA_H

#include "Math/Vector.h"



struct Camera {
    Vec3 position;
};


struct Camera *init_camara(void);
void camara_destroy(struct Camera *camera);

#endif //INC_3D_GRAPHICS_CAMERA_H
