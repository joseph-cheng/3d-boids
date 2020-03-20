#pragma once
#include "boid.h"
#include <vector>

std::vector<Boid> get_nearby_boids(Boid& boid, std::vector<Boid>& boids);

glm::vec3 limit(glm::vec3 v, float max);


