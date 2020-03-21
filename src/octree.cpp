#include "octree.h"
#include "boid.h"
#include "constants.h"
#include "aabb.h"
#include <glm/glm.hpp>
#include <vector>
#include <set>
#include <iostream>
#include <tuple>

Octree::Octree(AABB boundary) {
    nwb = nullptr;
    neb = nullptr;
    seb = nullptr;
    swb = nullptr;
    nwf = nullptr;
    nef = nullptr;
    sef = nullptr;
    swf = nullptr;
    parent = nullptr;


    this->boundary = boundary;

    boid = nullptr;
}

Octree::Octree(AABB boundary, Octree* parent) {
    nwb = nullptr;
    neb = nullptr;
    seb = nullptr;
    swb = nullptr;
    nwf = nullptr;
    nef = nullptr;
    sef = nullptr;
    swf = nullptr;

    this->parent = parent;

    this->boundary = boundary;

    boid = nullptr;

}

void Octree::subdivide() {
    float new_half_size = boundary.half_size/2.0f;
    nwb = new Octree(AABB(glm::vec3(boundary.centre.x - new_half_size,
                                    boundary.centre.y + new_half_size,
                                    boundary.centre.z - new_half_size),
                          new_half_size),
                          this);

    neb = new Octree(AABB(glm::vec3(boundary.centre.x + new_half_size,
                                    boundary.centre.y + new_half_size,
                                    boundary.centre.z - new_half_size),
                          new_half_size),
                          this);

    seb = new Octree(AABB(glm::vec3(boundary.centre.x + new_half_size,
                                    boundary.centre.y - new_half_size,
                                    boundary.centre.z - new_half_size),
                          new_half_size),
                          this);

    swb = new Octree(AABB(glm::vec3(boundary.centre.x - new_half_size,
                                    boundary.centre.y - new_half_size,
                                    boundary.centre.z - new_half_size),
                          new_half_size),
                          this);

    nwf = new Octree(AABB(glm::vec3(boundary.centre.x - new_half_size,
                                    boundary.centre.y + new_half_size,
                                    boundary.centre.z + new_half_size),
                          new_half_size),
                          this);


    nef = new Octree(AABB(glm::vec3(boundary.centre.x + new_half_size,
                                    boundary.centre.y + new_half_size,
                                    boundary.centre.z + new_half_size),
                          new_half_size),
                          this);

    sef = new Octree(AABB(glm::vec3(boundary.centre.x + new_half_size,
                                    boundary.centre.y - new_half_size,
                                    boundary.centre.z + new_half_size),
                          new_half_size),
                          this);

    swf = new Octree(AABB(glm::vec3(boundary.centre.x - new_half_size,
                                    boundary.centre.y - new_half_size,
                                    boundary.centre.z + new_half_size),
                          new_half_size),
                          this);

    if (boid->position.x >= boundary.centre.x) {
        if (boid->position.y >= boundary.centre.y) {
            if (boid->position.z >= boundary.centre.z) {
                nef->insert(boid);
            }
            else {
                neb->insert(boid);
            }
        }
        else {
            if (boid->position.z >= boundary.centre.z) {
                sef->insert(boid);
            }
                else {
                    seb->insert(boid);
                }
            }
        }
    else {
        if (boid->position.y >= boundary.centre.y) {
            if (boid->position.z >= boundary.centre.z) {
                nwf->insert(boid);
            }
            else {
                nwb->insert(boid);
            }
        }
        else {
            if (boid->position.z >= boundary.centre.z) {
                swf->insert(boid);
            }
            else {
                swb->insert(boid);
            }
        }
    }
    boid = nullptr;
}

bool Octree::insert(Boid* boid) {

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

void Octree::collapse() {
    if (all_children_empty()) {
        nwb = nullptr;
        nwf = nullptr;
        neb = nullptr;
        nef = nullptr;
        swb = nullptr;
        swf = nullptr;
        seb = nullptr;
        sef = nullptr;
        parent->collapse();
    }
}

bool Octree::remove(Boid* boid) {

    if (this->boid == boid) {
        this->boid = nullptr;

        if (parent != nullptr) {
            parent->collapse();
        }


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

Octree* Octree::get_boid_node(Boid* boid) {
    if (boid == this->boid) {
        return this;
    }
    if (boid->position.x >= boundary.centre.x) {
        if (boid->position.y >= boundary.centre.y) {
            if (boid->position.z >= boundary.centre.z) {
                return nef->get_boid_node(boid);
            }
            else {
                return neb->get_boid_node(boid);
            }
        }
        else {
            if (boid->position.z >= boundary.centre.z) {
                return sef->get_boid_node(boid);
            }
            else {
                return seb->get_boid_node(boid);
            }
        }
    }
    else {
        if (boid->position.y >= boundary.centre.y) {
            if (boid->position.z >= boundary.centre.z) {
                return nwf->get_boid_node(boid);
            }
            else {
                return nwb->get_boid_node(boid);
            }
        }
        else {
            if (boid->position.z >= boundary.centre.z) {
                return swf->get_boid_node(boid);
            }
            else {
                return swb->get_boid_node(boid);
            }
        }
    }
}

bool Octree::all_children_empty() {
    return nwb->boid == nullptr && nwb->nwb == nullptr &&
           nwf->boid == nullptr && nwf->nwb == nullptr &&
           neb->boid == nullptr && neb->nwb == nullptr &&
           nef->boid == nullptr && nef->nwb == nullptr &&
           swb->boid == nullptr && swb->nwb == nullptr &&
           swf->boid == nullptr && swf->nwb == nullptr &&
           seb->boid == nullptr && seb->nwb == nullptr &&
           sef->boid == nullptr && sef->nwb == nullptr;
}

void Octree::flatten(std::set<std::tuple<Boid*, Octree*>>& to_populate) {
    if (boid != nullptr) {
        to_populate.insert(std::make_tuple(boid, this));
    }
    if (nwb == nullptr) {
        return;
    }

    nwb->flatten(to_populate);
    nwf->flatten(to_populate);
    neb->flatten(to_populate);
    nef->flatten(to_populate);
    swb->flatten(to_populate);
    swf->flatten(to_populate);
    seb->flatten(to_populate);
    sef->flatten(to_populate);

}
