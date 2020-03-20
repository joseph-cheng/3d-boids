#pragma once
#include <glm/glm.hpp>

class AABB {
public:
    AABB();
    AABB(glm::vec3 centre, float half_size);
    glm::vec3 centre;
    float half_size;
    bool contains(glm::vec3 point);
    bool intersects(AABB other);
};
