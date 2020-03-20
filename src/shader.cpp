#include "shader.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const GLchar* vertex_shader_path, const GLchar* frag_shader_path, const GLchar* geom_shader_path) {

    std::string vertex_shader_source = read_shader_from_file(vertex_shader_path);
    std::string frag_shader_source = read_shader_from_file(frag_shader_path);
    std::string geom_shader_source = read_shader_from_file(geom_shader_path);

    unsigned int vertex_shader = compile_shader(vertex_shader_source, GL_VERTEX_SHADER);
    unsigned int frag_shader = compile_shader(frag_shader_source, GL_FRAGMENT_SHADER);
    unsigned int geom_shader = compile_shader(geom_shader_source, GL_GEOMETRY_SHADER);

    int success;
    char info_log[512];

    ID = glCreateProgram();
    glAttachShader(ID, vertex_shader);
    glAttachShader(ID, frag_shader);
    glAttachShader(ID, geom_shader);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, info_log);
        std::cout << "Failed to link shader program\n" << info_log << std::endl;
    }


    glDeleteShader(vertex_shader);
    glDeleteShader(frag_shader);
    glDeleteShader(geom_shader);
}

void Shader::use() {
    glUseProgram(ID);
}


std::string Shader::read_shader_from_file(const GLchar* shader_path) {

    std::string shader_source;
    std::ifstream shader_file;

    shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        shader_file.open(shader_path);

        std::stringstream shader_stream;
        shader_stream << shader_file.rdbuf();
        shader_file.close();
        shader_source = shader_stream.str();
    }
    catch (std::ifstream::failure e) {
        std::cout << "Failed to read shader file" << std::endl;
    }

    return shader_source;
}

unsigned int Shader::compile_shader(std::string shader_source, GLenum shader_type) {
    const char* shader_code_c_str = shader_source.c_str();

    unsigned int shader;
    int success;
    char info_log[512];


    shader = glCreateShader(shader_type);

    glShaderSource(shader, 1, &shader_code_c_str, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        std::cout << "Failed to compileshader\n" << info_log << std::endl;
    }

    return shader;


}

void Shader::set_matrix_4(const std::string& name, glm::mat4 value) {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
