# 3d-boids
Reynolds' Boids in 3D written in C++ and using OpenGL.

Boids are stored in an octree for quick retrieval of nearby boids.

## Compilation

First, compile glfw for your system.

Put the resulting static library in `lib/`, then run the following commands

`$ mkdir build`

`$ cd build`

`$ cmake ..`

`$ make`

You can now run using `./boids`
