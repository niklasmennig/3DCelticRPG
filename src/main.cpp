#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

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
Mesh spriteMesh;
Mesh screenQuad;
Shader shader;
Shader uiShader;
Texture floorTex;
Texture wallTex;
Texture swordTex;
Texture claymoreTex;
Texture deerTex;
Texture terminalTex;
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
    camera.rotationY += deltaMouseX * 20 * deltaTime;
    camera.rotationX += deltaMouseY * 20 * deltaTime;

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

void DrawMeshInstance(Mesh* mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
    glm::mat4 translationMat = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 rotationMat = glm::toMat4(glm::quat(glm::vec3(glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z))));
    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);
    glm::mat4 matrix = translationMat * rotationMat * scaleMat;
    shader.SetMatrix("model",matrix);
    mesh->Draw();
} 

void DrawMeshInstance(MeshInstance instance) {
    instance.texture->Use();
    DrawMeshInstance(instance.mesh, instance.position, instance.rotation, instance.scale);
}

void DrawLevel(Level* level) {
    for (int i = 0; i < level->instances.size(); i++) {
        DrawMeshInstance(level->instances[i]);
    }
}

void DrawSprite(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec2 uvTopLeft, glm::vec2 uvBotRight) {
    Vertex vertices[]{
        Vertex(-0.5f,  -0.5f, 0.0f,   uvTopLeft.x, uvBotRight.y),
        Vertex(0.5f,   -0.5f, 0.0f,    uvBotRight.x, uvBotRight.y),
        Vertex(-0.5f,   0.5f, 0.0f,   uvTopLeft.x, uvTopLeft.y),
        Vertex(-0.5f,   0.5f, 0.0f,   uvTopLeft.x, uvTopLeft.y),
        Vertex(0.5f,   -0.5f, 0.0f,    uvBotRight.x, uvBotRight.y),
        Vertex(0.5f,    0.5f, 0.0f,    uvBotRight.x, uvTopLeft.y),
    };
    spriteMesh.SetVertices(vertices, 6);
    spriteMesh.UpdateBuffers(GL_STATIC_DRAW);
    DrawMeshInstance(&spriteMesh, position, rotation, scale);
}

//RENDER FULL TEXTURE
void DrawSprite(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
    DrawSprite(position, rotation, scale, glm::vec2(), glm::vec2(1, 1));
}

void DrawBillboardSprite(glm::vec3 position, glm::vec3 scale, glm::vec2 uvTopLeft, glm::vec2 uvBotRight) {
    DrawSprite(position, glm::vec3(0, -camera.rotationY, 0), scale, uvTopLeft, uvBotRight);
}

//RENDER FULL TEXTURE
void DrawBillboardSprite(glm::vec3 position, glm::vec3 scale){
    DrawSprite(position, glm::vec3(0, -camera.rotationY, 0), scale, glm::vec2(), glm::vec2(1, 1));
}

void Draw() {
    glEnable(GL_DEPTH_TEST);
    shader.Use();
    shader.SetMatrix("projection", camera.getProjectionMatrix(320, 240));
    shader.SetMatrix("view",camera.getViewMatrix());

    DrawLevel(&level);

    deerTex.Use();
    DrawBillboardSprite(glm::vec3(3, 0, 3), glm::vec3(1,1,1));

    glDisable(GL_DEPTH_TEST);
    shader.SetMatrix("view", camera.getViewMatrixUntransformed());
    //Draw Left Hand Item
    swordTex.Use();
    DrawSprite(glm::vec3(0.5f,0,0),glm::vec3(25,0,0), glm::vec3(1.0,1.0,1.0));

    //Draw Right Hand Item
    claymoreTex.Use();
    DrawMeshInstance(&spriteMesh,glm::vec3(-0.5f,0,0),glm::vec3(25,0,0), glm::vec3(1.0,1.0,1.0));
}


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
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

    shader = Loader::LoadShaderFromFile("./res/StandardShader.vert", "./res/StandardShader.frag");
    uiShader = Loader::LoadShaderFromFile("./res/UIShader.vert", "./res/UIShader.frag");
    floorTex = Loader::LoadTextureFromFile("./res/dirtGround.png");
    wallTex = Loader::LoadTextureFromFile("./res/stoneWall.png");
    terminalTex = Loader::LoadTextureFromFile("./res/terminal.png");

    swordTex = Loader::LoadTextureFromFile("./res/schwert.png");
    claymoreTex = Loader::LoadTextureFromFile("./res/breitschwert.png");
    deerTex = Loader::LoadTextureFromFile("./res/reh.png");

    wallMesh = MeshHelper::CreateWallMesh(glm::vec2(0,0), glm::vec2(1,1));
    floorMesh = MeshHelper::CreateFloorMesh(glm::vec2(0, 0), glm::vec2(1, 1));
    spriteMesh = MeshHelper::CreateSpriteMesh(glm::vec2(0, 0), glm::vec2(1, 1));

    Vertex quadVerts[]{
        Vertex(-0.5f, 0, 0, 0, 1),
        Vertex( 0.5f, 0, 0, 1, 1),
        Vertex( 0.5f, 1, 0, 1, 0),
        Vertex( 0.5f, 1, 0, 1, 0),
        Vertex(-0.5f, 1, 0, 0, 0),
        Vertex(-0.5f, 0, 0, 0, 1),
    };
    screenQuad.GenerateBuffers();
    screenQuad.SetVertices(quadVerts, 6);
    screenQuad.UpdateBuffers();

    ppBuffer.GenerateBuffer(640, 480);

    shader.Use();
    

    while (!glfwWindowShouldClose(window)) {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        deltaMouseX = mouseX - lastMouseX;
        deltaMouseY = mouseY - lastMouseY;
        double newTime = glfwGetTime();
        deltaTime = newTime - lastTime;
        glfwPollEvents();
        Update();
        ppBuffer.Bind();
        glClearColor(0, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Draw();
        ppBuffer.Unbind();

        uiShader.Use();
        uiShader.SetMatrix("projection", glm::ortho(-0.5, 0.5, 0.0, 1.0, -0.5, 0.5));
        uiShader.SetMatrix("view", glm::lookAt(glm::vec3(0, -1, 0), glm::vec3(0, -1, 1), glm::vec3(0, 1, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0,0,1)));
        ppBuffer.UseTexture();
        glClear(GL_COLOR_BUFFER_BIT);
        screenQuad.Draw();
        //terminalTex.Use();
        //DrawSprite(glm::vec3(), glm::vec3(0,0,180), glm::vec3(1, 1, 1));

        glfwSwapBuffers(window);
        lastMouseX = mouseX;
        lastMouseY = mouseY;
        lastTime = newTime;
    }

    Loader::CleanUp();

    glfwDestroyWindow(window);
}