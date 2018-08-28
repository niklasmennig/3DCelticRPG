#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "Shader.h"

namespace Loader {
    Shader CreateShaderFromFile(const char* vertexShaderPath, const char* fragmentShaderPath) {
        std::string vertSource;
        std::string fragSource;

        std::ifstream vStream(vertexShaderPath);

        while(vStream.good()) {
            vertSource += vStream.get();
        }
        vStream.close();

        std::cout << vertSource << std::endl;

        std::ifstream fStream(fragmentShaderPath);

        while (fStream.good())
        {
            fragSource += fStream.get();
        }
        fStream.close();

        std::cout << fragSource << std::endl;

        return Shader(vertSource.c_str(), fragSource.c_str());
    }
}