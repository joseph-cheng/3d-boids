#include "system.h"
#include "constants.h"
#include "boid.h"
#include "aabb.h"
#include <cstdlib>
#include <vector>
#include <glm/glm.hpp>
#include <iostream>
#include <set>
#include <tuple>

System::System(int boids_to_generate) {
    boids_tree = new Octree(AABB(glm::vec3(0.0f), WORLD_RADIUS));
    for (int i=0; i < boids_to_generate; i++) {
        float x = (float)std::rand() / (float)RAND_MAX * 2.0f * WORLD_RADIUS - WORLD_RADIUS;
        float y = (float)std::rand() / (float)RAND_MAX * 2.0f * WORLD_RADIUS - WORLD_RADIUS;
        float z = (float)std::rand() / (float)RAND_MAX * 2.0f * WORLD_RADIUS - WORLD_RADIUS;
        Boid* b = new Boid(x,y,z,i);
        boids_tree->insert(b);
        boids.push_back(b);
    }
}

void System::update(float boid_data[], glm::vec3 player_pos) {
    int i = 0;
    for (Boid* boid : boids) {
        std::vector<Boid*> nearby_boids = boids_tree->get_nearby_boids(boid);
        Octree* octree_with_boid = boids_tree->get_boid_node(boid);

        glm::vec3 sep = boid->separation(nearby_boids);
        glm::vec3 coh = boid->cohesion(nearby_boids);
        glm::vec3 ali = boid->alignment(nearby_boids);
        glm::vec3 avo = boid->avoid(player_pos) / 10.0f;


        boid->apply_force(coh+sep+ali);
        boid->update();


        if (!octree_with_boid->boundary.contains(boid->position)) {
            octree_with_boid->remove(boid);
            boids_tree->insert(boid);
        }

        boid_data[i*6] = boid->position.x;
        boid_data[i*6+1] = boid->position.y;
        boid_data[i*6+2] = boid->position.z;

        boid_data[i*6+3] = boid->velocity.x;
        boid_data[i*6+4] = boid->velocity.y;
        boid_data[i*6+5] = boid->velocity.z;

        i++;
    }

}
