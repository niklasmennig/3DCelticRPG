#pragma once
#include "GL/glew.h"
#include "glm/glm.hpp"

struct Shader {
    int shaderProgram;
    Shader(){}
    Shader(const char* vertexShaderSource, const char* fragmentShaderSource) {
        int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glUseProgram(shaderProgram);
    }
    void Use() {
        glUseProgram(shaderProgram);
    }
    void SetMatrix(const char* name, glm::mat4 matrix)
    {
        GLint location;
        location = glGetUniformLocation(shaderProgram, name);
        glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
    }
};