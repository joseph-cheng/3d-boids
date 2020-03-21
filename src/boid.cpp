#include "boid.h"
#include "util.h"
#include "constants.h"
#include <vector>
#include <glm/glm.hpp>
#include <iostream>

Boid::Boid(float x, float y, float z, int ID) {
    this->position = glm::vec3(x, y, z);
    this->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    this->acceleration = glm::vec3 (0.0f, 0.0f, 0.0f);
    this->ID = ID;

}

glm::vec3 Boid::separation(std::vector<Boid*>& nearby_boids) {

    glm::vec3 steer = glm::vec3(0.0f, 0.0f, 0.0f);
    int num_nearby_boids = (int)nearby_boids.size() - 1;

    for (Boid* boid : nearby_boids) {
        if (boid == this) {
            continue;
        }
        glm::vec3 diff = this->position - boid->position;
        float d = glm::length(diff);
        steer += glm::normalize(diff)/d;
    }

    if (num_nearby_boids != 0) {
        steer /= (float)num_nearby_boids;
    }
    if (glm::length(steer) != 0.0f) {
        steer = limit(glm::normalize(steer) * MAX_SPEED - velocity, MAX_FORCE);
    }

    return steer;
}

glm::vec3 Boid::alignment(std::vector<Boid*>& nearby_boids) {
    glm::vec3 steer = glm::vec3(0.0f, 0.0f, 0.0f);

    int num_nearby_boids = (int)nearby_boids.size() - 1;

    for (Boid* boid : nearby_boids) {
        if (boid == this) {
            continue;
        }
        steer += boid->velocity;
    }

    if (num_nearby_boids != 0) {
        steer = steer / (float)num_nearby_boids;
    }
    if (glm::length(steer) != 0.0f) {
        steer = limit(glm::normalize(steer) * MAX_SPEED - velocity, MAX_FORCE);
    }

    return steer;
}



glm::vec3 Boid::cohesion(std::vector<Boid*>& nearby_boids) {

    glm::vec3 position_sum = glm::vec3(0.0f, 0.0f, 0.0f);

    int num_nearby_boids = (int)nearby_boids.size() - 1;
    
    for (Boid* boid : nearby_boids) {
        if (boid == this) {
            continue;
        }
        position_sum += boid->position;
    }

    glm::vec3 steer = glm::vec3(0.0f, 0.0f, 0.0f);

    if (num_nearby_boids != 0) {
        position_sum = position_sum / (float)num_nearby_boids;
        steer = position_sum - position;
        steer = limit(glm::normalize(steer) * MAX_SPEED - velocity, MAX_FORCE);
    }
    return steer;
}

glm::vec3 Boid::avoid(glm::vec3 predator_position) {
    glm::vec3 steer = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 diff = this->position - predator_position;
    float d = glm::length(diff);
    steer = glm::normalize(diff)/d;

    steer = limit(glm::normalize(steer) * MAX_SPEED - velocity, MAX_FORCE);

    return steer;
}


const float Boid::squared_distance(Boid& other) {
    glm::vec3 vector_between = other.position - this->position;
    return vector_between.x * vector_between.x + 
           vector_between.y * vector_between.y + 
           vector_between.z * vector_between.z;
}

void Boid::apply_force(glm::vec3 force) {
    this->acceleration += force;
}

void Boid::update() {
    this->velocity += this->acceleration;
    this->velocity = limit(this->velocity, MAX_SPEED);
    this->position += this->velocity;

    if (this->position.x >= WORLD_RADIUS) {
        this->position.x = -WORLD_RADIUS + EPSILON;
    }
    else if (this->position.x <= -WORLD_RADIUS) {
        this->position.x = WORLD_RADIUS - EPSILON;
    }

    if (this->position.y >= WORLD_RADIUS) {
        this->position.y = -WORLD_RADIUS + EPSILON;
    }
    else if (this->position.y <= -WORLD_RADIUS) {
        this->position.y = WORLD_RADIUS - EPSILON;
    }

    if (this->position.z >= WORLD_RADIUS) {
        this->position.z = -WORLD_RADIUS + EPSILON;
    }
    else if (this->position.z <= -WORLD_RADIUS) {
        this->position.z = WORLD_RADIUS - EPSILON;
    }

    this->acceleration *= 0.0f;

}

bool Boid::operator==(Boid& other) {
    return this->ID == other.ID;
}

bool Boid::operator!=(Boid& other) {
    return not(*this == other);
}
