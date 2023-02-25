#include "Window.hpp"
#include <iostream>

Window::Window(const unsigned int width, const unsigned int height, std::string_view const& name)
    : width(width)
    , height(height)
    , name(name) {};

Window::Window(std::string_view const& name)
    : name(name)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "Couldn't initialize SDL\n";
        exit(EXIT_FAILURE);
    }

    SDL_DisplayMode displaymode;
    SDL_GetCurrentDisplayMode(0, &displaymode);

    this->height = displaymode.h;
    this->width = displaymode.w;
};

Window::~Window()
{
    SDL_DestroyWindow(this->sdl_window);
}

void Window::create()
{
    this->sdl_window = SDL_CreateWindow(
        this->name.cbegin(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        this->width, this->height, SDL_WINDOW_BORDERLESS);

    if (this->sdl_window == nullptr) {
        std::cerr << "[ERROR] Unable to create SDL WINDOW\n";
        exit(EXIT_FAILURE);
    }
}

unsigned int Window::getWidth() const
{
    return this->width;
};

unsigned int Window::getHeight() const
{
    return this->height;
};