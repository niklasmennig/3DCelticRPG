#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Mesh.h"
#include "Camera.h"
#include "MeshInstance.h"
#include "MeshHelper.h"
#include "Shader.h"
#include "Texture.h"
#include "LevelBuilder.h"
#include "Loader.h"
#include "PostProcessing.h"

GLFWwindow *window;
Camera camera;
Mesh wallMesh;
Mesh floorMesh;
Mesh screenQuad;
Shader shader;
Shader uiShader;
Texture floorTex;
Texture wallTex;
FrameBuffer ppBuffer;
double deltaTime;
double lastTime;
double lastMouseX;
double deltaMouseX;
double lastMouseY;
double deltaMouseY;

std::string levelTxt =
    "##########################/"
    "#------------------------#/"
    "#-----##########---------#/"
    "#------------------------#/"
    "#------------------------#/"
    "#------------------------#/"
    "#---------####-----------#/"
    "#------------------------#/"
    "#------------------------#/"
    "#------------------------#/"
    "##########################/";

Level level = LevelBuilder::BuildLevel(levelTxt, &wallMesh, &floorMesh, &wallTex, &floorTex);

void Update() {
    camera.rotationY += deltaMouseX * deltaTime;
    camera.rotationX += deltaMouseY * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, 1);
    }

    if (glfwGetKey(window, GLFW_KEY_W))
        camera.Move(0, 1.0f * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S))
        camera.Move(0, -1.0f * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A))
        camera.Move(-1.0f * deltaTime, 0);
    if (glfwGetKey(window, GLFW_KEY_D))
        camera.Move(1.0f * deltaTime, 0);
    //std::cout << 1.0f / deltaTime << std::endl;
    //std::cout << camera.rotationX << std::endl;
}

void DrawMeshInstance(Mesh* mesh, glm::vec3 position) {
    glm::mat4 matrix = camera.getViewMatrix();
    matrix = glm::translate(matrix, position);
    shader.SetMVP(matrix);
    mesh->Draw();
} 

void DrawMeshInstance(MeshInstance instance) {
    instance.texture->Use();
    DrawMeshInstance(instance.mesh, instance.position);
}

void DrawLevel(Level* level) {
    for (int i = 0; i < level->instances.size(); i++) {
        DrawMeshInstance(level->instances[i]);
    }
}

void Draw() {
    glm::mat4 matrix = camera.getViewMatrix();
    shader.SetMVP(matrix);

    DrawLevel(&level);
}


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    window = glfwCreateWindow(640, 480, "RPG", NULL, NULL);

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    shader = Loader::CreateShaderFromFile("./res/StandardShader.vert", "./res/StandardShader.frag");
    uiShader = Loader::CreateShaderFromFile("./res/UIShader.vert", "./res/UIShader.frag");
    floorTex = Texture("./res/dirtGround.png");
    wallTex = Texture("./res/stoneWall.png");

    wallMesh = MeshHelper::CreateWallMesh(glm::vec2(0,0), glm::vec2(1,1));
    floorMesh = MeshHelper::CreateFloorMesh(glm::vec2(0, 0), glm::vec2(1, 1));

    Vertex quadVerts[]{
        Vertex(-1, -1, 0, -1, -1),
        Vertex(1, -1, 0, 1, -1),
        Vertex(1, 1, 0, 1, 1),
        Vertex(1, 1, 0, 1, 1),
        Vertex(-1, 1, 0, -1, 1),
        Vertex(-1, -1, 0, -1, -1),
    };
    screenQuad.GenerateBuffers();
    screenQuad.SetVertices(quadVerts, 6);
    screenQuad.UpdateBuffers();

    ppBuffer.GenerateBuffer(320, 240);

    while (!glfwWindowShouldClose(window)) {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        deltaMouseX = mouseX - lastMouseX;
        deltaMouseY = mouseY - lastMouseY;
        double newTime = glfwGetTime();
        deltaTime = newTime - lastTime;
        glfwPollEvents();
        Update();
        glClearColor(0, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ppBuffer.Bind();
        Draw();
        ppBuffer.Unbind();
        uiShader.Use();
        ppBuffer.UseTexture();
        screenQuad.Draw();

        glfwSwapBuffers(window);
        lastMouseX = mouseX;
        lastMouseY = mouseY;
        lastTime = newTime;
    }

    glfwDestroyWindow(window);
}