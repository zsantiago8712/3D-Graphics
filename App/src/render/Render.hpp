#pragma once
#include <LA/vec2.hpp>
#include <SDL2/SDL.h>
#include <vector>

namespace hasbu {

class Render {

public:
    Render() = default;
    ~Render();

    void create(const unsigned int width, const unsigned int height, SDL_Window* ptr_sdl_window);

    SDL_Renderer* m_ptr_sdl_renderer;
    SDL_Texture* m_color_buffer_texture;

    std::vector<unsigned int> m_color_buffer;
    unsigned int m_previous_frame_time = 0;

    void draw(std::vector<std::array<la::vec2, 3>> const& points, unsigned int num_points);
    void update_time();

private:
    unsigned int m_color_buffer_width;
    unsigned int m_color_buffer_height;

    void render_color_buffer() const;
    void clear_color_buffer(unsigned int color);
    void render_grid(const unsigned int grid_size, const unsigned int color);

    void draw_pixel(unsigned int color, unsigned int x, unsigned int y);
    void draw_rectangle(int width, int height, int x_rectangle, int y_rectangle, unsigned int color);
    void draw_triangle(unsigned int x0, unsigned int y0, unsigned x1,
        unsigned y1, unsigned int x2, unsigned y2, unsigned color);

    void draw_line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int color);
};

}