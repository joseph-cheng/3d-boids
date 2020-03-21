#pragma once
#include "aabb.h"
#include <set>
#include <vector>
#include <tuple>
#include "boid.h"

// octree with capacity 1
class Octree {
    public:
        Octree(AABB boundary);
        Octree(AABB boundary, Octree* parent);
        std::vector<Boid*> get_nearby_boids(Boid* boid);
        bool insert(Boid* boid);
        bool remove(Boid* boid);
        Octree* get_boid_node(Boid* boid);
        ~Octree();
        AABB boundary;
        void flatten(std::set<std::tuple<Boid*, Octree*>>& to_populate);

    private:
        Octree* nwb;
        Octree* neb;
        Octree* seb;
        Octree* swb;
        Octree* nwf;
        Octree* nef;
        Octree* sef;
        Octree* swf;

        Octree* parent;


        Boid* boid;

        void subdivide();

        void query_range(AABB range, std::vector<Boid*>& to_populate);

        void collapse();
        bool all_children_empty();


};
