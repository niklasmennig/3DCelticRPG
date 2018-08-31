#pragma once

#include "glm/glm.hpp"
#include "GL/glew.h"
#include "Mesh.h"
#include "Texture.h"

struct MeshInstance{
    Mesh *mesh;
    Texture *texture;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    MeshInstance(Mesh* m, glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, Texture* tex) {
        mesh = m;
        position = pos;
        rotation = rot;
        texture = tex;
        scale = scl;
    }
};