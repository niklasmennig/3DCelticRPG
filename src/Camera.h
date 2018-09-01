#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Utilities.h"
#include <math.h>


struct Camera {
    glm::vec3 position = glm::vec3(2.5f,0.0f,2.5f);
    float rotationY;
    float rotationX;

    glm::mat4 getProjectionMatrix(int screenWidth, int screenHeight) {
        return glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
    }

    glm::mat4 getViewMatrix() {
        rotationX = Utilities::Clamp(rotationX, -45.0f, 45.0f);
        glm::mat4 res;
        res = glm::rotate(glm::mat4(1.0f), glm::radians(rotationX), glm::vec3(1, 0, 0));
        res = glm::rotate(res, glm::radians(rotationY), glm::vec3(0, 1, 0));
        glm::mat4 view = glm::lookAt(position, position + glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
        res *= view;
        return res;
    }

    glm::mat4 getViewMatrixUntransformed() {
        return glm::lookAt(glm::vec3(0,0,-1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    }

    glm::vec3 getRightVector() {
        return glm::vec3(-cos(glm::radians(rotationY)), 0, -sin(glm::radians(rotationY)));
    }

    glm::vec3 getForwardVectorFlat() {
        return glm::vec3(-sin(glm::radians(rotationY)), 0, cos(glm::radians(rotationY)));
    }

    void Move(float x, float y) {
        position += getRightVector() * x + getForwardVectorFlat() * y;
    }
};