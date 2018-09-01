#pragma once

#include "GL/glew.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Shader.h"
#include "Texture.h"

namespace Loader {

enum ContentType
{
    SHADER,
    TEXTURE
};

class LoadedContent
{
  public:
    unsigned int id;
    ContentType type;
    LoadedContent(int ID, ContentType TYPE)
    {
        id = ID;
        type = TYPE;
    }
};

static std::vector<LoadedContent> loadedContent;

void CleanUp()
{
    for (int i = 0; i < Loader::loadedContent.size(); i++)
    {
        switch (Loader::loadedContent[i].type)
        {
        case Loader::ContentType::SHADER:
            glDeleteProgram(Loader::loadedContent[i].id);
            break;
        case Loader::ContentType::TEXTURE:
            glDeleteTextures(1, &Loader::loadedContent[i].id);
            break;
        }
    }
}

Shader LoadShaderFromFile(const char *vertexShaderPath, const char *fragmentShaderPath)
{
    std::string vertSource;
    std::string fragSource;

    std::ifstream vStream(vertexShaderPath);

    while (vStream.good())
    {
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

    Shader res(vertSource.c_str(), fragSource.c_str());
    Loader::loadedContent.push_back(Loader::LoadedContent(res.shaderProgram, Loader::ContentType::SHADER));
    return res;
}

Texture LoadTextureFromFile(const char *path)
{
    Texture res = Texture(path);
    Loader::loadedContent.push_back(Loader::LoadedContent(res.texture, Loader::ContentType::TEXTURE));
    return res;
}
}