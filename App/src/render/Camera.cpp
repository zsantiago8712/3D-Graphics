#include "Camera.hpp"

namespace hasbu {

Camera::Camera(la::vec3 const& pos)
    : position(pos) {};

/**
 * @brief Updates the camera position and ray
 *
 * @param vertex
 */
void Camera::update(la::vec3 const& vertex)
{
    this->position -= vertex;
}

la::vec3 Camera::getPosition() const
{
    return this->position;
}
}