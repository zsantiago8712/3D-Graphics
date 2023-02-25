#pragma once
#include <platform/Window.hpp>
#include <render/Render.hpp>
#include <string_view>

namespace hasbu {

class App {
public:
    App();
    explicit App(std::string_view const& appName);
    void run();

private:
    Window window;
    Render render;
    SDL_Event m_sdl_event;

    void init();
    bool process_input();
};

}