#include "Callbacks.h"


void framebufferCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    auto* app = (AppWindow*)glfwGetWindowUserPointer(window);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        app->camera.ProcessKeyboard(FORWARD, app->deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        app->camera.ProcessKeyboard(BACKWARD, app->deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        app->camera.ProcessKeyboard(LEFT, app->deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        app->camera.ProcessKeyboard(RIGHT, app->deltaTime);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        app->bf.resetTerrain();
        app->bf.genFaultFormation(128, 128, 0, 1, 0.3, 1);
        app->bf.setScalingFactor(1, 2, 1);
        app->bf.generateTerrain();
        app->bf.modelSetup();
    }
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
