#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Utilities.h"
#include <math.h>


struct Camera {
    glm::vec3 position = glm::vec3(0.5f,0.0f,-2);
    float rotationY;
    float rotationX;
    glm::mat4 getViewMatrix() {
        rotationX = Utilities::Clamp(rotationX, glm::radians(-45.0f), glm::radians(45.0f));
        glm::mat4 res;
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.0f);
        proj = glm::rotate(proj, rotationX, glm::vec3(1, 0, 0));
        proj = glm::rotate(proj, rotationY, glm::vec3(0, 1, 0));
        glm::mat4 view = glm::lookAt(position, position + glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
        res = proj * view;
        return res;
    }
    void Move(float x, float y) {
        position.x += -cos(rotationY) * x - sin(rotationY) * y;
        position.z += -sin(rotationY) * x + cos (rotationY) * y;
    }
};