#include "aabb.h"
#include <glm/glm.hpp>

AABB::AABB() {
    this->centre = glm::vec3(0.0f, 0.0f, 0.0f);
    this->half_size = 1.0f;
}

AABB::AABB(glm::vec3 centre, float half_size) {
    this->centre = centre;
    this->half_size = half_size;
}

bool AABB::contains(glm::vec3 point) {
    return point.x > centre.x - half_size &&
           point.x < centre.x + half_size &&
           point.y > centre.y - half_size &&
           point.y < centre.y + half_size;
}

bool AABB::intersects(AABB other) {
    return centre.x - half_size < other.centre.x + other.half_size &&
           centre.x + half_size > other.centre.x - other.half_size &&
           centre.y - half_size < other.centre.y + other.half_size &&
           centre.y + half_size > other.centre.y - other.half_size &&
           centre.z - half_size < other.centre.z + other.half_size &&
           centre.z + half_size > other.centre.z - other.half_size;

}
