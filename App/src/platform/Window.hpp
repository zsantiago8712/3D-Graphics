#pragma once
#include "../defines.hpp"
#include <SDL2/SDL.h>
#include <string_view>

class HB_EXPORT Window {

public:
    HB_EXPORT explicit Window(std::string_view const& name);
    HB_EXPORT Window(unsigned int width, unsigned int height, std::string_view const& name);
    ~Window();

    SDL_Window* sdl_window = nullptr;

    void create();

    unsigned int getWidth() const;
    unsigned int getHeight() const;

private:
    unsigned int width;
    unsigned int height;
    const std::string_view name;
};