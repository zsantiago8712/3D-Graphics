#pragma once
#include "details/_vec3_f.hpp"
#include <array>
#include <cstddef>
#include <string_view>
#include <vector>

#include <LA/vec2.hpp>
#include <LA/vec3.hpp>

namespace hasbu {

struct Vertex {
    Vertex() = default;
    ~Vertex() = default;

    std::vector<std::array<la::vec2, 3>> m_points;
    unsigned int m_numPoints = 0;

    std::vector<la::vec3> m_vertices;
    std::vector<la::vec3> m_faces;

    void update(la::vec3 const& camera_position, const unsigned int window_width, const unsigned int window_height);
};

struct Mesh {

    Mesh() = default;
    ~Mesh() = default;

    std::vector<Vertex> m_vertex;
    bool load_model(std::vector<std::string_view> const& files_path);
    la::vec3 update(la::vec3 const& camera_position);
};

}