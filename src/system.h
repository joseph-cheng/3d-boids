#pragma once
#include "boid.h"
#include "octree.h"
#include <vector>
#include <glm/glm.hpp>

class System {
    public:
        System(int boids_to_generate);
        Octree* boids_tree;
        std::vector<Boid*> boids;

        void update(float boid_data[], glm::vec3 player_pos);

};
