#pragma once
#include "GL/glew.h"
#include <iostream>

struct Texture{
    unsigned int texture;
    Texture() {}
    Texture(const char *path);
    void Use() {
        glBindTexture(GL_TEXTURE_2D, texture);
    }
};