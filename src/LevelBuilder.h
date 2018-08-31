#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "MeshInstance.h"
#include "glm/glm.hpp"
#include <string>
#include <vector>

struct Level {
    std::vector<MeshInstance> instances;
};

namespace LevelBuilder {
    Level BuildLevel(std::string levelString, Mesh* wallMesh, Mesh* floorMesh, Texture* wallTex, Texture* floorTex) {
        Level result;
        int x = 0;
        int y = 0;
        for (int i = 0; i < levelString.length(); i++) {
            switch(levelString[i]) {
                case '#':
                    result.instances.push_back(MeshInstance(wallMesh, glm::vec3(x, 0, y), glm::vec3(), glm::vec3(1,1,1), wallTex));
                    break;
                case '-':
                    result.instances.push_back(MeshInstance(floorMesh, glm::vec3(x, -0.5f, y), glm::vec3(), glm::vec3(1,1,1), floorTex));
                    break;
                case '/':
                    y++;
                    x = 0;
                    break;
            }
            x++;
        }
        return result;
    }
}