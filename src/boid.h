#pragma once
#include <vector>
#include <glm/glm.hpp>

class Boid {
private:
    int ID;
public:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;

    Boid(float x, float y, float z, int ID);

    glm::vec3 separation(std::vector<Boid*>& nearby_boids);
    glm::vec3 alignment(std::vector<Boid*>& nearby_boids);
    glm::vec3 cohesion(std::vector<Boid*>& nearby_boids);
    glm::vec3 avoid(glm::vec3 predator_position);


    const float squared_distance(Boid& other);

    void apply_force(glm::vec3 force);

    void update();

    bool operator==(Boid& other);
    bool operator!=(Boid& other);
};
