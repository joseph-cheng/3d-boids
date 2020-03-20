#include "camera.h"
#include "constants.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <cmath>

Camera::Camera() {
    camera_pos = glm::vec3(0.0f, 0.0f, 2.0f * WORLD_RADIUS);
    camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
    camera_up = glm::vec3(0.0f, 1.0f, 0.0f);

    fov = 90.0f;

    pitch = 0.0f;
    yaw = -90.0f;

    camera_speed = 0.01f;
    sensitivity = 0.05f;

    last_mouse_x = NULL;
    last_mouse_y = NULL;
   
}

void Camera::update() {
    camera_front = glm::normalize(glm::vec3(cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
                                            sin(glm::radians(pitch)),
                                            sin(glm::radians(yaw)) * cos(glm::radians(pitch))));
}


// Generates lookat matrix
glm::mat4 Camera::gen_lookat_matrix() {
    return glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);
}

// Generates projection matrix, near and far planes at 0.1 and 100.0 respectively
glm::mat4 Camera::gen_proj_matrix() {
    return glm::perspective(glm::radians(fov/2.0f), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 100.0f);
}

float Camera::get_move_speed() { return camera_speed; }
float Camera::get_sensitivity() { return sensitivity; }

glm::vec3 Camera::get_camera_front() { return camera_front; }
glm::vec3 Camera::get_camera_up() { return camera_up; }
