#include "octree.h"
#include "boid.h"
#include "constants.h"
#include "aabb.h"
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

Octree::Octree(AABB boundary) {
    nwb = nullptr;
    neb = nullptr;
    seb = nullptr;
    swb = nullptr;
    nwf = nullptr;
    nef = nullptr;
    sef = nullptr;
    swf = nullptr;

    this->boundary = boundary;

    boid = nullptr;
}

void Octree::subdivide() {
    float new_half_size = boundary.half_size/2.0f;
    nwb = new Octree(AABB(glm::vec3(boundary.centre.x - new_half_size,
                                    boundary.centre.y + new_half_size,
                                    boundary.centre.z - new_half_size),
                          new_half_size));

    neb = new Octree(AABB(glm::vec3(boundary.centre.x + new_half_size,
                                    boundary.centre.y + new_half_size,
                                    boundary.centre.z - new_half_size),
                          new_half_size));

    seb = new Octree(AABB(glm::vec3(boundary.centre.x + new_half_size,
                                    boundary.centre.y - new_half_size,
                                    boundary.centre.z - new_half_size),
                          new_half_size));

    swb = new Octree(AABB(glm::vec3(boundary.centre.x - new_half_size,
                                    boundary.centre.y - new_half_size,
                                    boundary.centre.z - new_half_size),
                          new_half_size));

    nwf = new Octree(AABB(glm::vec3(boundary.centre.x - new_half_size,
                                    boundary.centre.y + new_half_size,
                                    boundary.centre.z + new_half_size),
                          new_half_size));


    nef = new Octree(AABB(glm::vec3(boundary.centre.x + new_half_size,
                                    boundary.centre.y + new_half_size,
                                    boundary.centre.z + new_half_size),
                          new_half_size));

    sef = new Octree(AABB(glm::vec3(boundary.centre.x + new_half_size,
                                    boundary.centre.y - new_half_size,
                                    boundary.centre.z + new_half_size),
                          new_half_size));

    swf = new Octree(AABB(glm::vec3(boundary.centre.x - new_half_size,
                                    boundary.centre.y - new_half_size,
                                    boundary.centre.z + new_half_size),
                          new_half_size));
}

bool Octree::insert(Boid* boid) {

    if (!boundary.contains(boid->position)) {
        return false;
    }

    if (this->boid == nullptr) {
        this->boid = boid;
        return true;
    }

    if (nwb == nullptr) {
        subdivide();
    }

    if (boid->position.x >= boundary.centre.x) {
        if (boid->position.y >= boundary.centre.y) {
            if (boid->position.z >= boundary.centre.z) {
                return nef->insert(boid);
            }
            else {
                return neb->insert(boid);
            }
        }
        else {
            if (boid->position.z >= boundary.centre.z) {
                return sef->insert(boid);
            }
            else {
                return seb->insert(boid);
            }
        }
    }
    else {
        if (boid->position.y >= boundary.centre.y) {
            if (boid->position.z >= boundary.centre.z) {
                return nwf->insert(boid);
            }
            else {
                return nwb->insert(boid);
            }
        }
        else {
            if (boid->position.z >= boundary.centre.z) {
                return swf->insert(boid);
            }
            else {
                return swb->insert(boid);
            }
        }
    }
}

bool Octree::remove(Boid* boid) {

    if (!boundary.contains(boid->position)) {
        return false;
    }

    if (this->boid == boid) {
        this->boid = nullptr;
        return true;
    }

    if (boid->position.x >= boundary.centre.x) {
        if (boid->position.y >= boundary.centre.y) {
            if (boid->position.z >= boundary.centre.z) {
                return nef->remove(boid);
            }
            else {
                return neb->remove(boid);
            }
        }
        else {
            if (boid->position.z >= boundary.centre.z) {
                return sef->remove(boid);
            }
            else {
                return seb->remove(boid);
            }
        }
    }
    else {
        if (boid->position.y >= boundary.centre.y) {
            if (boid->position.z >= boundary.centre.z) {
                return nwf->remove(boid);
            }
            else {
                return nwb->remove(boid);
            }
        }
        else {
            if (boid->position.z >= boundary.centre.z) {
                return swf->remove(boid);
            }
            else {
                return swb->remove(boid);
            }
        }
    }
}

Octree::~Octree() {
    delete nwb;
    delete neb;
    delete seb;
    delete swb;
    delete nwf;
    delete nef;
    delete sef;
    delete swf;
}


void Octree::query_range(AABB range, std::vector<Boid*>& to_populate) {
    if (!boundary.intersects(range)) {
        return;
    }

    if (boid != nullptr) {
        if (range.contains(boid->position)) {
            to_populate.push_back(boid);
        }
    }
    if (nwb == nullptr) {
        return;
    }

    nwb->query_range(range, to_populate);
    neb->query_range(range, to_populate);
    seb->query_range(range, to_populate);
    swb->query_range(range, to_populate);
    nwf->query_range(range, to_populate);
    nef->query_range(range, to_populate);
    sef->query_range(range, to_populate);
    swf->query_range(range, to_populate);
}

std::vector<Boid*> Octree::get_nearby_boids(Boid* boid) {
    std::vector<Boid*> nearby_boids;
    query_range(AABB(boid->position, NEIGHBOURHOOD), nearby_boids);
    return nearby_boids;
}


