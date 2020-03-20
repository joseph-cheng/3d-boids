#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <string>

class Shader {
    private:
        // id of this shader
        unsigned int ID;

        // given path to shader, read and return contents
        std::string read_shader_from_file(const GLchar* shader_path);


        // compile and return a shader's id
        unsigned int compile_shader(std::string shader_source, GLenum shader_type);
    public:
        // compiles shader
        Shader(const GLchar* vertex_shader_path, const GLchar* frag_shader_path, const GLchar* geom_shader_path);

        void set_matrix_4(const std::string& name, glm::mat4 value);

        // sets current shader to this one
        void use();
};


