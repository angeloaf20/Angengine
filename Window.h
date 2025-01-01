#pragma once
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Camera.h"
#include "Constants.h"

void createWindow(GLFWwindow** window);
void processInput(GLFWwindow* window, Camera* cam, double deltaTime);
void mouseCallback(GLFWwindow* window, double xPosIn, double yPosIn);