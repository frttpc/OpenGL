#pragma once
#ifndef MOUSE_HPP
#define MOUSE_HPP
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

class Mouse {

public:

    static void cursorPositionCallback(GLFWwindow* _, double x, double y) {};

private:

};

float mouseX = 0, mouseY = 0, yaw = 0, pitch = 0;
float lastX = 400, lastY = 300;
bool firstMouse = true;


static void cursorPositionCallback(GLFWwindow* _, double x, double y)
{

    mouseX = 2.0 * ((float)x / Window::width) - 1;
    mouseY = 2.0 * (1.0 - ((float)y / Window::height)) - 1;
}

#endif