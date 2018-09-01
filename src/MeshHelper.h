#pragma once

#include "glm/glm.hpp"
#include "Mesh.h"

namespace MeshHelper {
    Mesh CreateFloorMesh(glm::vec2 uvTopLeft, glm::vec2 uvBotRight) {
        Vertex vertices[]{
            Vertex( 0.5f, 0.0f,  0.5f, uvBotRight.x, uvTopLeft.y ),
            Vertex(-0.5f, 0.0f, -0.5f, uvTopLeft.x, uvBotRight.y),
            Vertex( 0.5f, 0.0f, -0.5f, uvBotRight.x, uvBotRight.y ),
            Vertex( 0.5f, 0.0f,  0.5f, uvBotRight.x, uvTopLeft.y ),
            Vertex(-0.5f, 0.0f,  0.5f, uvTopLeft.x, uvTopLeft.y ),
            Vertex(-0.5f, 0.0f, -0.5f, uvTopLeft.x, uvBotRight.y ),
        };
        Mesh res;
        res.GenerateBuffers();
        res.SetVertices(vertices, 6);
        res.UpdateBuffers();
        return res;
    }
    Mesh CreateWallMesh(glm::vec2 uvTopLeft, glm::vec2 uvBotRight)
    {
        Vertex vertices[]{
            
            Vertex(-0.5f, -0.5f, -0.5f, uvTopLeft.x, uvBotRight.y),
            Vertex(-0.5f, 0.5f, 0.5f, uvBotRight.x, uvTopLeft.y),
            Vertex(-0.5f, -0.5f, 0.5f, uvBotRight.x, uvBotRight.y),
            Vertex(-0.5f, 0.5f, -0.5f, uvTopLeft.x, uvTopLeft.y),
            Vertex(-0.5f, 0.5f, 0.5f, uvBotRight.x, uvTopLeft.y),
            Vertex(-0.5f, -0.5f, -0.5f, uvTopLeft.x, uvBotRight.y),
            

            Vertex(0.5f, 0.5f, 0.5f, uvBotRight.x, uvTopLeft.y),
            Vertex(0.5f, -0.5f, -0.5f, uvTopLeft.x, uvBotRight.y),
            Vertex(0.5f, -0.5f, 0.5f, uvBotRight.x, uvBotRight.y),
            Vertex(0.5f, -0.5f, -0.5f, uvTopLeft.x, uvBotRight.y),
            Vertex(0.5f, 0.5f, 0.5f, uvBotRight.x, uvTopLeft.y),
            Vertex(0.5f, 0.5f, -0.5f, uvTopLeft.x, uvTopLeft.y),

            Vertex(-0.5f, -0.5f, -0.5f, uvTopLeft.x, uvBotRight.y),
            Vertex(0.5f, -0.5f, -0.5f, uvBotRight.x, uvBotRight.y),
            Vertex(0.5f, 0.5f, -0.5f, uvBotRight.x, uvTopLeft.y),
            Vertex(0.5f, 0.5f, -0.5f, uvBotRight.x, uvTopLeft.y),
            Vertex(-0.5f, 0.5f, -0.5f, uvTopLeft.x, uvTopLeft.y),
            Vertex(-0.5f, -0.5f, -0.5f, uvTopLeft.x, uvBotRight.y),

            Vertex(-0.5f, -0.5f, 0.5f, uvTopLeft.x, uvBotRight.y),
            Vertex(0.5f, 0.5f, 0.5f, uvBotRight.x, uvTopLeft.y),
            Vertex(0.5f, -0.5f, 0.5f, uvBotRight.x, uvBotRight.y),
            Vertex(0.5f, 0.5f, 0.5f, uvBotRight.x, uvTopLeft.y),
            Vertex(-0.5f, -0.5f, 0.5f, uvTopLeft.x, uvBotRight.y),
            Vertex(-0.5f, 0.5f, 0.5f, uvTopLeft.x, uvTopLeft.y),
        };
        Mesh res;
        res.GenerateBuffers();
        res.SetVertices(vertices, 24);
        res.UpdateBuffers();
        return res;
    }

    Mesh CreateSpriteMesh(glm::vec2 uvTopLeft, glm::vec2 uvBotRight) {
        Vertex vertices[]{
            Vertex(-0.5f,-0.5f, 0.0f, uvTopLeft.x, uvBotRight.y),
            Vertex( 0.5f,-0.5f, 0.0f, uvBotRight.x, uvBotRight.y),
            Vertex(-0.5f, 0.5f, 0.0f, uvTopLeft.x, uvTopLeft.y),
            Vertex(-0.5f, 0.5f, 0.0f, uvTopLeft.x, uvTopLeft.y),
            Vertex( 0.5f,-0.5f, 0.0f, uvBotRight.x, uvBotRight.y),
            Vertex( 0.5f, 0.5f, 0.0f, uvBotRight.x, uvTopLeft.y),
        };
        Mesh res;
        res.GenerateBuffers();
        res.SetVertices(vertices, 6);
        res.UpdateBuffers();
        return res;
    }
}