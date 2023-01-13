//
// Created by Santiago Zamora on 20/12/22.
//

#include "Camera/Camera.h"
#include "Math/Vector.h"
#include <stdlib.h>
#include <stdio.h>

struct Camera *init_camara(void) {

  const Vec3 init_position = {0, 0, 0};
  struct Camera *camera = malloc(sizeof(struct Camera));

  if (camera == NULL) {
	fprintf(stderr, "No hay suficiente memoria\n");
	exit(EXIT_FAILURE);
  }

  camera->position = init_position;
  return camera;
}

void camara_destroy(struct Camera *camera) {
  free(camera);
  camera = NULL;
}
