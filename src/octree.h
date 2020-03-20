#pragma once
#include "aabb.h"
#include <vector>
#include "boid.h"

// octree with capacity 1
class Octree {
    public:
        Octree(AABB boundary);
        std::vector<Boid*> get_nearby_boids(Boid* boid);
        bool insert(Boid* boid);
        bool remove(Boid* boid);
        ~Octree();

    private:
        Octree* nwb;
        Octree* neb;
        Octree* seb;
        Octree* swb;
        Octree* nwf;
        Octree* nef;
        Octree* sef;
        Octree* swf;

        AABB boundary;

        Boid* boid;

        void subdivide();

        void query_range(AABB range, std::vector<Boid*>& to_populate);


};
