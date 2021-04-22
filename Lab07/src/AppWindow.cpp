#include "AppWindow.h"


AppWindow::AppWindow()
{



}

AppWindow::~AppWindow()
{
    Terminate();
}

void AppWindow::Init(std::string title, int h, int w)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    gameWindow = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
    if (gameWindow == nullptr)
    {
        glfwTerminate();
    }
    else
    {
        std::cout << "GLFW Started!" << std::endl;
    }

    SCR_HEIGHT = (unsigned int)h;
    SCR_WIDTH = (unsigned int)w;

    camera.lastX = (float)SCR_WIDTH / 2.0f;
    camera.lastY = (float)SCR_HEIGHT / 2.0f;

    /* Make the window's context current */
    glfwMakeContextCurrent(gameWindow);

    /* Make GLFW capture the mouse*/
    glfwSetInputMode(gameWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetWindowUserPointer(gameWindow, this);
    FrameBuffer();
    MouseCallback();
    ScrollCallback();

    /*Init GLAD*/
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    /*Set Depth for OpenGL*/
    glEnable(GL_DEPTH_TEST);

    terrain.Init();
    WorldToTerrainHeight(camera.Position);

    skybox.Init();

    Camera c(15.0f, WorldToTerrainHeight(glm::vec3(15.0f, 0.0f, 11.0f))  + 1.5f, 11.0, 0.f, 1.0f, 0.f, 90.9f, -37.f);
    camera = c;

    std::cout << "Loading MD2 Files..." << std::endl;
    CMD2Model m =  CMD2Model("./res/Shaders/mVert.glsl", "./res/Shaders/mFrag.glsl");
    md2Model = m;
    CMD2Model weapon =  CMD2Model("./res/Shaders/mVert.glsl", "./res/Shaders/mFrag.glsl");
    md2ModelWeapon = weapon;

    animState = md2Model.StartAnimation(SALUTE);
    position.y = WorldToTerrainHeight(position) + 1.5f;
    md2Model.setPos(position);
    md2ModelWeapon.setPos(position);
    md2Model.LoadModel("./res/Models/Ogro/Tris.MD2","./res/Models/Ogro/Ogrobase.jpg");
    md2ModelWeapon.LoadModel("./res/Models/Ogro/Weapon.md2", "./res/Models/Ogro/Weapon.jpg");

}
void AppWindow::Run()
{
    Render();
}

void AppWindow::Buffer()
{
    glfwSwapBuffers(gameWindow);
    glfwPollEvents();
}

void AppWindow::Terminate()
{
    glfwTerminate();
}

bool AppWindow::GameInput()
{
    int state = glfwGetKey(gameWindow, GLFW_KEY_W);

    if (state == GLFW_PRESS)
    {
        std::cout << "W pressed in AppWindow.cpp file" << std::endl;
        return true;
    }


    return false;
}

void AppWindow::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void AppWindow::FrameBuffer()
{
    glfwSetFramebufferSizeCallback(gameWindow, framebufferCallback);
}

//For NOW WE WILL HAVE TERRAIN HERE, WILL BREAK OFF SOON
void AppWindow::Projection()
{
    //glActiveTexture(GL_TEXTURE0);

    // view/projection transformations
    projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100000.0f);
    view = camera.GetViewMatrix();

    // world transformation
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
}

void AppWindow::SetShader(Shader shader)
{
    shader.use();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    shader.setMat4("model", model);
}

void AppWindow::Restart()
{
    glPrimitiveRestartIndex(0xFFFFFFFFU);
    glEnable(GL_PRIMITIVE_RESTART);
}

void AppWindow::MouseCallback()
{
    glfwSetCursorPosCallback(gameWindow, mouse_callback);
}


void AppWindow::ScrollCallback()
{
    glfwSetScrollCallback(gameWindow, scroll_callback);
}

void AppWindow::InputCallback()
{
    processInput(gameWindow);
}

void AppWindow::Render()
{
    while (!glfwWindowShouldClose(gameWindow))
    {
        //std::cout << "Camera: X: " << camera.Position.x << " -- Y: " << camera.Position.y << " -- Z: " << camera.Position.z << std::endl;
        currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        InputCallback();

        Clear();

        Projection();

        UpdatePlayer();

        terrain.Render(projection, view, camera.Position);

        //MD2 Render Here
        if(animations)
        {
            md2Model.RenderModel(&animState, projection, view, md2Model.GetPos(), rotation, direction);
            md2Model.UpdateAnimation(&animState, deltaTime);
            if(weapon)
            {
                md2ModelWeapon.RenderModel(&animState, projection, view, md2ModelWeapon.GetPos(), rotation, direction);
            }
        }
        else
        {
            md2Model.RenderModel(nullptr, projection, view, md2Model.GetPos(), rotation, direction);
            if(weapon)
            {
                md2ModelWeapon.RenderModel(nullptr, projection, view, md2ModelWeapon.GetPos(), rotation, direction);
            }
        }




        view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
        skybox.Draw(view, projection);

        Buffer();
    }

}

//Any player updates per frame go here
void AppWindow::UpdatePlayer()
{


}

/*void AppWindow::GenerateTerrain()
{
    //bf.LoadHeightField("height128.raw", 128);
    bf.genFaultFormation(128, 128, 0, 1, 0.3, 1);
    bf.setScalingFactor(1, 2, 1);

    LoadTextures();

    bf.generateTerrain();
    bf.modelSetup();
}

void AppWindow::LoadTextures()
{
    terrainGrassTextureID = tl.loadTexture("./res/textures/grass/Grass004_1K_Color.jpg");
    terrainGrassNormalTextureID = tl.loadTexture("./res/textures/grass/Grass004_1K_Normal.jpg");

    terrainDirtTextureID = tl.loadTexture("./res/textures/dirt/Ground044_1K_Color.jpg");
    terrainDirtNormalTextureID = tl.loadTexture("./res/textures/dirt/Ground044_1K_Normal.jpg");

    terrainMountainTextureID = tl.loadTexture("./res/textures/mountain/Rock007_1K_Color.jpg");
    terrainMountainNormalTextureID = tl.loadTexture("./res/textures/mountain/Rock007_1K_Normal.jpg");

    terrainSnowTextureID = tl.loadTexture("./res/textures/snow/Snow005_1K_Color.jpg");
    terrainSnowNormalTextureID = tl.loadTexture("./res/textures/snow/Snow005_1K_Normal.jpg");

    s.use();
    s.setInt("dirtTexture", 0);
    s.setInt("dirtNormalTexture", 1);

    s.setInt("grassTexture", 2);
    s.setInt("grassNormalTexture", 3);

    s.setInt("mountainTexture", 4);
    s.setInt("mountainNormalTexture", 5);

    s.setInt("snowTexture", 6);
    s.setInt("snowNormalTexture", 7);
}*/

void framebufferCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void AppWindow::processInput(GLFWwindow* window)
{
    auto* app = (AppWindow*)glfwGetWindowUserPointer(window);

    float y = WorldToTerrainHeight(camera.Position);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        app->camera.ProcessKeyboard(FORWARD, app->deltaTime, y);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        app->camera.ProcessKeyboard(BACKWARD, app->deltaTime, y);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        app->camera.ProcessKeyboard(LEFT, app->deltaTime, y);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        app->camera.ProcessKeyboard(RIGHT, app->deltaTime, y);

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        app->terrain.SetWireFlag(true);
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        app->terrain.SetWireFlag(false);

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    animations = true;
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        animations = false;
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        weapon = true;
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        weapon = false;
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        animState = md2Model.StartAnimation(STAND);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        animState = md2Model.StartAnimation(RUN);
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        animState = md2Model.StartAnimation(ATTACK);
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        animState = md2Model.StartAnimation(WAVE);
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        animState = md2Model.StartAnimation(PAIN_A);
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
        animState = md2Model.StartAnimation(PAIN_B);
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
        animState = md2Model.StartAnimation(FLIP);
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
        animState = md2Model.StartAnimation(JUMP);

    float speed = 5;

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        direction = 0.0f;
        position.x += speed * deltaTime;
        position.y = WorldToTerrainHeight(position) + 1.5f;
        md2Model.setPos(position);
        md2ModelWeapon.setPos(position);
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        direction = 40.5f;
        position.x -= speed * deltaTime;
        position.y = WorldToTerrainHeight(position) + 1.5f;
        md2Model.setPos(position);
        md2ModelWeapon.setPos(position);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        direction = 215.0f;
        position.z -= speed * deltaTime;
        position.y = WorldToTerrainHeight(position) + 1.5f;
        md2Model.setPos(position);
        md2ModelWeapon.setPos(position);
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        direction = 180.5f;
        position.z += speed * deltaTime;
        position.y = WorldToTerrainHeight(position) + 1.5f;
        md2Model.setPos(position);
        md2ModelWeapon.setPos(position);
    }

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        std::cout << "Resetting Terrain!" << std::endl;
        app->terrain.ResetTerrain();
    }
}

float AppWindow::WorldToTerrainHeight(glm::vec3 p)
{
    float worldx, worldz, worldToTerrainScaleFactor;
    worldToTerrainScaleFactor = 5.12;
    worldx = p.x * worldToTerrainScaleFactor;
    worldz = p.z * worldToTerrainScaleFactor;
    p.y = (terrain.GetHeight((int)worldx, (int)worldz) / worldToTerrainScaleFactor);
    p.y /= 10.0f;
    return p.y + 1.5f;
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    auto* app = (AppWindow*)glfwGetWindowUserPointer(window);

    if (app->camera.firstMouse)
    {
        app->camera.lastX = (float)xpos;
        app->camera.lastY = (float)ypos;
        app->camera.firstMouse = false;
    }

    float xoffset = (float)xpos - app->camera.lastX;
    float yoffset = app->camera.lastY - (float)ypos; // reversed since y-coordinates go from bottom to top

    app->camera.lastX = (float)xpos;
    app->camera.lastY = (float)ypos;

    app->camera.ProcessMouseMovement(xoffset, yoffset);

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    auto* app = (AppWindow*)glfwGetWindowUserPointer(window);
    app->camera.ProcessMouseScroll((float)yoffset);
}