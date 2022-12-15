//
// Created by Santiago Zamora on 30/10/22.
//

#ifndef INC_3D_GRAPHICS_WINDOW_H
#define INC_3D_GRAPHICS_WINDOW_H

#include <SDL2/SDL.h>


struct Window{

    SDL_Window *ptr_sdl_window;
    char window_name[20];

};



struct Window *init_window(const char window_name[20]);

void window_destroy(struct Window *window);





#endif //INC_3D_GRAPHICS_WINDOW_H
