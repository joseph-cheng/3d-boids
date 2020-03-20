#pragma once
#include <glm/glm.hpp>

class Camera {
    public:
        Camera();
        glm::mat4 gen_lookat_matrix();
        glm::mat4 gen_proj_matrix();
        

        glm::vec3 camera_pos;

        float get_move_speed();
        float get_sensitivity();

        glm::vec3 get_camera_front();
        glm::vec3 get_camera_up();

        float pitch;
        float yaw;

        double last_mouse_x;
        double last_mouse_y;

        void update();

    private:
        // Position of camera in world coordinates

        // Unit vector in the direction the camera is facing
        // This is equivalent to a unit vector in the direction of the z-axis in camera space
        glm::vec3 camera_front;

        // Unit vector in the direction of 'up' in camera space
        // This is equivalent to a unit vector in the direction of the y-axis in camera space
        glm::vec3 camera_up;

        // Fov of the camera, measured in degrees
        float fov;

        float camera_speed;
        float sensitivity;

};
