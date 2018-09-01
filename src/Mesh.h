#pragma once

#include "glm/glm.hpp"
#include "GL/glew.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 uv;
    Vertex(float x, float y, float z, float r, float g, float b, float u, float v) {
        position = glm::vec3(x, y, z);
        color = glm::vec3(r, g, b);
        uv = glm::vec2(u, v);
    }
    Vertex(float x, float y, float z, float u, float v)
    {
        position = glm::vec3(x, y, z);
        color = glm::vec3(1,1,1);
        uv = glm::vec2(u,v);
    }
    Vertex(float x, float y, float z) {
        position = glm::vec3(x, y, z);
        color = glm::vec3(1,1,1);
        uv = glm::vec2();
    }
};

class Mesh {
    public:
    Vertex* vertices;
    GLuint VAO, VBO;
    GLsizei vertexCount;
    void GenerateBuffers() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
    }
    void SetVertices(Vertex* verts, int vertCount) {
        vertices = verts;
        vertexCount = vertCount;
    }
    void SetPosition(int vertNr, float x, float y, float z) {
        vertices[vertNr].position = glm::vec3(x, y, z);
    }
    void SetColor(int vertNr, float r, float g, float b) {
        vertices[vertNr].color = glm::vec3(r, g, b);
    }
    void SetUV(int vertNr, float u, float v) {
        vertices[vertNr].uv = glm::vec2(u, v);
    }
    void UpdateBuffers(GLenum usage) {
        glBindVertexArray(VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount, vertices, usage);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    void UpdateBuffers() {
        UpdateBuffers(GL_STATIC_DRAW);
    }
    void Draw() {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
};