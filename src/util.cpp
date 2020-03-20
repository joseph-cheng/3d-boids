#include <vector>
#include "util.h"
#include "boid.h"
#include "constants.h"

std::vector<Boid> get_nearby_boids(Boid& boid, std::vector<Boid>& boids) {
    std::vector<Boid> nearby_boids;

    for (auto& other : boids) {
        if (other != boid) {
            if (boid.squared_distance(other) <= NEIGHBOURHOOD * NEIGHBOURHOOD) {
                nearby_boids.push_back(other);
            }
        }
    }
    return nearby_boids;
}


glm::vec3 limit(glm::vec3 v, float max) {
    if (length(v) > max) {
        return normalize(v) * max;
    }
    return v;
}
