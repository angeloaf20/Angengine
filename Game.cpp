#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Window.h"
#include "Renderer.h"

#include <iostream>
#include <vector>
#include <string>


int main(int argc, char* argv[])
{
    GLFWwindow* window;
    bool gameRunning = false;

    createWindow(&window);

    Renderer* mainRenderer = new Renderer();

    Camera* cam = new Camera(glm::vec3(0.0f, 15.5f, 8.5f));
    cam->Pitch = -45.0f;
    glfwSetWindowUserPointer(window, cam);
    glfwSetCursorPosCallback(window, mouseCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    double lastTime = glfwGetTime();
    double deltaTime = 0.0;
    int frameCount = 0;
    double fpsTimer = 0.0;

    while (!glfwWindowShouldClose(window))
    {
        processInput(window, cam, deltaTime);
        

        double currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        frameCount++;
        fpsTimer += deltaTime;

        if (fpsTimer >= 1.0) // Update FPS every 1 second
        {
            double fps = static_cast<double>(frameCount) / fpsTimer;

            std::string title = "Angengine FPS: " + std::to_string(fps);
            glfwSetWindowTitle(window, title.c_str());

            frameCount = 0;
            fpsTimer = 0.0;
        }

        mainRenderer->drawScene(deltaTime, cam);
        glfwSwapBuffers(window);
    }
    
    delete mainRenderer;
    glfwDestroyWindow(window);

    return 0;
}