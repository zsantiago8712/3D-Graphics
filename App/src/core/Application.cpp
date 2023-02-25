#include "Application.hpp"
#include <iostream>
#include <mesh/Mesh.hpp>
#include <render/Camera.hpp>

namespace hasbu {

App::App(std::string_view const& appName)
    : window(appName) {};

App::App()
    : window("App") {};

void App::run()
{
    init();
    Mesh mesh;
    Camera camera;
    mesh.load_model({ "/Users/randymarsh/Developer/3D-Graphics/assets/cube.obj", "/Users/randymarsh/Developer/3D-Graphics/assets/cube.obj" });

    while (process_input()) {
        render.update_time();
        mesh.m_vertex[0].update(camera.getPosition(), window.getWidth(), window.getHeight());
        render.draw(mesh.m_vertex[0].m_points, mesh.m_vertex[0].m_numPoints);
    }
}

void App::init()
{
    window.create();
    render.create(window.getWidth(), window.getHeight(), window.sdl_window);
}

bool App::process_input()
{
    SDL_PollEvent(&m_sdl_event);
    switch (m_sdl_event.type) {
    case SDL_QUIT:
        return false;

    case SDL_KEYDOWN:
        if (m_sdl_event.key.keysym.sym == SDLK_ESCAPE) {
            return false;
        }
        return true;

    default:
        return true;
    }

    return true;
}

}