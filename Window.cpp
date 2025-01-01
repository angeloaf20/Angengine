#include "Window.h"

bool firstMouse = true;

void createWindow(GLFWwindow** window) 
{
    if (!glfwInit())
    {
        std::cout << "COULD NOT INITIALIZE GLFW\n" << std::endl;
        exit(EXIT_FAILURE);
        return;
    }

    *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Angengine", NULL, NULL);

    if (!*window)
    {
        glfwTerminate();
        std::cout << "COULD NOT CREATE GLFW WINDOW\n" << std::endl;
        exit(EXIT_FAILURE);
        return;
    }

    glfwMakeContextCurrent(*window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
}

void keysCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void processInput(GLFWwindow* window, Camera* cam, double deltaTime)
{
    glfwPollEvents();
    glfwSetKeyCallback(window, keysCallback);

    float cameraSpeed = 5.0f;

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraSpeed *= 2.5f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam->Position += (float)deltaTime * cameraSpeed * cam->Front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam->Position -= (float) deltaTime * cameraSpeed * cam->Front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam->Position += (float)deltaTime * cameraSpeed * glm::normalize(glm::cross(cam->Up, cam->Front));
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam->Position -= (float)deltaTime * cameraSpeed * glm::normalize(glm::cross(cam->Up, cam->Front));
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cam->Position += (float)deltaTime * cameraSpeed * cam->Up;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        cam->Position += (float)deltaTime * -cameraSpeed * cam->Up;
} 

void mouseCallback(GLFWwindow* window, double xPosIn, double yPosIn)
{
    static double lastX = xPosIn;
    static double lastY = yPosIn;

    if (firstMouse)
    {
        lastX = xPosIn;
        lastY = yPosIn;
        firstMouse = false;
    }

    double xOffset = xPosIn - lastX;
    double yOffset = lastY - yPosIn; // Reversed since y-coordinates go from bottom to top

    lastX = xPosIn;
    lastY = yPosIn;

    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (camera)
    {
        camera->rotateCamera(xOffset, yOffset);
    }
}