//
// Created by Santiago Zamora on 30/10/22.
//

#ifndef INC_3D_GRAPHICS_APP_H
#define INC_3D_GRAPHICS_APP_H


#include "Window/Window.h"
#include "Renderer/Renderer.h"





struct App{

    struct Window *window;
    struct Renderer *renderer;
    SDL_Event event;

};


void init_app(struct App *app);


void app_destroy(struct App *app);


void app_run(struct App *app);





#endif //INC_3D_GRAPHICS_APP_H
