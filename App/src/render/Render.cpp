#include "Render.hpp"
#include <cmath>
#include <iostream>

#define FPS 60
#define FRAME_TARGET (1000 / FPS)

namespace hasbu {

Render::~Render()
{
    SDL_DestroyRenderer(m_ptr_sdl_renderer);
}

void Render::create(const unsigned int width, const unsigned int height, SDL_Window* ptr_sdl_window)
{
    m_color_buffer_height = height;
    m_color_buffer_width = width;
    m_ptr_sdl_renderer = SDL_CreateRenderer(ptr_sdl_window, -1, 0);
    if (m_ptr_sdl_renderer == nullptr) {
        std::cerr << "Couldn't create SDL Render\n";
    }

    m_color_buffer_texture = SDL_CreateTexture(m_ptr_sdl_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
        m_color_buffer_width, m_color_buffer_height);

    m_color_buffer.resize(m_color_buffer_height * m_color_buffer_width);
}

void Render::draw(const std::vector<std::array<la::vec2, 3>>& points, const unsigned int num_points)
{
    for (unsigned int i = 0; i < num_points; i++) {
        draw_rectangle(3, 3, static_cast<int>(points[i][0].x), static_cast<int>(points[i][0].y), 0XFF0000);
        draw_rectangle(3, 3, static_cast<int>(points[i][1].x), static_cast<int>(points[i][1].y), 0XFF0000);
        draw_rectangle(3, 3, static_cast<int>(points[i][2].x), static_cast<int>(points[i][2].y), 0XFF0000);

        draw_triangle(
            static_cast<int>(points[i][0].x), static_cast<int>(points[i][0].y),
            static_cast<int>(points[i][1].x), static_cast<int>(points[i][1].y),
            static_cast<int>(points[i][2].x), static_cast<int>(points[i][2].y),
            0x296E01);
    }

    render_grid(20, 0xFFFFFF);
    render_color_buffer();
    clear_color_buffer(0x000000);
    SDL_RenderPresent(m_ptr_sdl_renderer);
}

void Render::update_time()
{
    const unsigned int time_to_wait = FRAME_TARGET - ((unsigned int)SDL_GetTicks64() - m_previous_frame_time);
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET) {
        SDL_Delay(time_to_wait);
    }
    m_previous_frame_time = SDL_GetTicks();
}

void Render::render_color_buffer() const
{
    SDL_UpdateTexture(m_color_buffer_texture, nullptr,
        m_color_buffer.data(), (m_color_buffer_width * sizeof(unsigned int)));

    SDL_RenderCopy(m_ptr_sdl_renderer, m_color_buffer_texture, nullptr, nullptr);
}

void Render::clear_color_buffer(const unsigned int color)
{
    for (unsigned int y = 0; y < m_color_buffer_height; y++) {

        for (unsigned int x = 0; x < m_color_buffer_width; x++) {
            draw_pixel(color, x, y);
        }
    }
}

void Render::render_grid(const unsigned int grid_size, const unsigned int color)
{
    for (int y = 0; y < m_color_buffer_height; y += grid_size) {
        for (int x = 0; x < m_color_buffer_width; x += grid_size) {
            draw_pixel(color, x, y);
        }
    }
}

void Render::draw_pixel(const unsigned int color, const unsigned int x, const unsigned int y)
{
    if ((x < m_color_buffer_width && x >= 0) && (y < m_color_buffer_height && y >= 0)) {
        m_color_buffer[(m_color_buffer_width * y) + x] = color;
    }
}

void Render::draw_rectangle(const int width, const int height, const int x_rectangle, const int y_rectangle, const unsigned int color)
{
    for (int y = y_rectangle; y < (y_rectangle + height); y++) {
        for (int x = x_rectangle; x < (width + x_rectangle); x++) {
            draw_pixel(color, x, y);
        }
    }
}

void Render::draw_triangle(const unsigned int x0, const unsigned int y0, const unsigned x1,
    const unsigned y1, const unsigned int x2, const unsigned y2, const unsigned color)
{
    draw_line(x0, y0, x1, y1, color);
    draw_line(x1, y1, x2, y2, color);
    draw_line(x2, y2, x0, y0, color);
}

void Render::draw_line(const unsigned int x0,
    const unsigned int y0, const unsigned int x1,
    const unsigned int y1, const unsigned int color)
{
    const int delta_x = (x1 - x0);
    const int delta_y = (y1 - y0);

    const unsigned int lenght_side = (abs(delta_x) >= abs(delta_y)) ? abs(delta_x) : abs(delta_y);

    const float x_inc = static_cast<float>(delta_x) / static_cast<float>(lenght_side);
    const float y_inc = static_cast<float>(delta_y) / static_cast<float>(lenght_side);

    auto current_x = static_cast<float>(x0);
    auto current_y = static_cast<float>(y0);

    for (int i = 0; i <= lenght_side; i++) {
        draw_pixel(color, static_cast<unsigned int>(roundf(current_x)), static_cast<unsigned int>(roundf(current_y)));
        current_x += x_inc;
        current_y += y_inc;
    }
}

}