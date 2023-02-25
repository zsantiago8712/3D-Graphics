#include <LA/vec3.hpp>

namespace hasbu {

class Camera {

public:
    Camera() = default;
    explicit Camera(la::vec3 const& pos);

    void update(la::vec3 const& vertex);
    la::vec3 getPosition() const;

private:
    la::vec3 position {};
};

}