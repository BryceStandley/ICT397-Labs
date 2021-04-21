#pragma once
#include "Texture.h"
#include "Window.h"
#include <glm/glm.hpp>
#include <iostream>
#include "Terrain.h"
#include "Camera.h"
#include "Skybox.h"
#include "CMD2Model.h"



class AppWindow
{
public:
    AppWindow();
    ~AppWindow();
    virtual void Init(std::string title, int h, int w);
    virtual void Buffer();
    virtual bool GameInput();
    void Terminate();
    virtual void Clear();
    virtual void FrameBuffer();
    virtual void MouseCallback();
    virtual void ScrollCallback();
    virtual void InputCallback();
    virtual void Projection();
    virtual void SetShader(Shader shader);
    virtual void Restart();
    virtual void Run();
    virtual void UpdatePlayer();

    virtual void Render();
    //virtual void GenerateTerrain();
    //virtual void LoadTextures();



    void processInput(GLFWwindow* window);

    Camera camera;
    float currentFrame = 0.0f;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    Terrain terrain;
    Skybox skybox = {};

private:
    Input gameInput;
    GLFWwindow* gameWindow = nullptr;
    glm::vec3 lightPos = glm::vec3(48.0f, 5.0f, 45.3f);

    unsigned int SCR_WIDTH = 800;
    unsigned int SCR_HEIGHT = 600;

    TextureLoader tl;
    CMD2Model md2Model;
    CMD2Model md2ModelWeapon;
    animationState animState;
    glm::vec3 position = glm::vec3(50.0f, 0.0f, 50.0f);
    bool animations = false;
    bool weapon = true;
    float rotation = 180.695f;
    float direction = 0.0f;
    /*unsigned int terrainGrassTextureID;
    unsigned int terrainGrassNormalTextureID;
    unsigned int terrainDirtTextureID;
    unsigned int terrainDirtNormalTextureID;
    unsigned int terrainMountainTextureID;
    unsigned int terrainMountainNormalTextureID;
    unsigned int terrainSnowTextureID;
    unsigned int terrainSnowNormalTextureID;
     */
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);

    float WorldToTerrainHeight(glm::vec3);
};

void framebufferCallback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);