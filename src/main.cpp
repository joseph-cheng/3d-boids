#include "shader.h"
#include "camera.h"
#include "constants.h"
#include "boid.h"
#include "util.h"
#include "system.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>


void keyboard_input(GLFWwindow* window) {
    Camera* camera = (Camera*)glfwGetWindowUserPointer(window);
    float camera_move_speed = camera->get_move_speed();
    glm::vec3 camera_front = camera->get_camera_front();
    glm::vec3 camera_up = camera->get_camera_up();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera->camera_pos += camera_move_speed * camera_front;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera->camera_pos -= camera_move_speed * camera_front;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera->camera_pos += camera_move_speed * glm::normalize(glm::cross(camera_front, camera_up));
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera->camera_pos -= camera_move_speed * glm::normalize(glm::cross(camera_front, camera_up));
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    Camera* camera = (Camera*)glfwGetWindowUserPointer(window);

    float sensitivity = camera->get_sensitivity();

    if (camera->last_mouse_x == NULL) {
        camera->last_mouse_x = xpos;
        camera->last_mouse_y = ypos;
    }

    float x_offset = xpos - camera->last_mouse_x;
    float y_offset = camera->last_mouse_y - ypos;

    camera->last_mouse_x = xpos;
    camera->last_mouse_y = ypos;

    camera->yaw += x_offset * sensitivity;
    camera->pitch += y_offset * sensitivity;

    if (camera->pitch > 89.0f) {
        camera->pitch = 89.0f;
    }
    else if (camera->pitch < -89.0f) {
        camera->pitch = -89.0f;
    }
}


int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Boids", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialise GLAD" << std::endl;
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    glEnable(GL_DEPTH_TEST);

    Shader shader("../src/vert.glsl", "../src/frag.glsl", "../src/geom.glsl");

    System* system = new System(NUM_BOIDS);

    float boid_data[6 * NUM_BOIDS];


    unsigned int VAO;
    unsigned int VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(boid_data), boid_data, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    Camera* camera = new Camera();
    glfwSetWindowUserPointer(window, camera);




    while (!glfwWindowShouldClose(window)) {
        keyboard_input(window);
        glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        system->update(boid_data, camera->camera_pos);
        camera->update();


        shader.use();
        glm::mat4 proj = camera->gen_proj_matrix();
        glm::mat4 view = camera->gen_lookat_matrix();

        shader.set_matrix_4("proj_mat", proj);
        shader.set_matrix_4("view_mat", view);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(boid_data), boid_data);
        glDrawArrays(GL_LINES, 0, NUM_BOIDS);
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}
