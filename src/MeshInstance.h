#pragma once

#include "glm/glm.hpp"
#include "GL/glew.h"
#include "Mesh.h"
#include "Texture.h"

struct MeshInstance{
    Mesh *mesh;
    Texture *texture;
    glm::vec3 position;

    MeshInstance(Mesh* m, glm::vec3 pos, Texture* tex) {
        mesh = m;
        position = pos;
        texture = tex;
    }
};