#pragma once

#include "GL/glew.h"

class FrameBuffer {
    public:
    unsigned int id;
    unsigned int texture;
    void GenerateBuffer(int width, int height) {
        glGenFramebuffers(1, &id);
        glBindFramebuffer(GL_FRAMEBUFFER, id);
        glDrawBuffer(GL_COLOR_ATTACHMENT0);

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    void Bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, id);
    }
    void Unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    void UseTexture() {
        glBindTexture(GL_TEXTURE_2D, texture);
    }
};