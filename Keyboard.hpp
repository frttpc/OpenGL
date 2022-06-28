#pragma once
#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Mouse.hpp"
#include "Window.hpp"
#include "Scene.hpp"

using namespace std;

class Keyboard {

public:

    static void keyCallback(GLFWwindow* _, int key, int scancode, int action, int mods){}


private:

};

int moveFront = 0, moveRight = 0, jumpForce = 0;
float velocityY = 0;
bool dash = false, jumping = false;


void keyCallback(GLFWwindow* _, int key, int scancode, int action, int mods)
{
    /////  WASD
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        moveFront = 1;
    }
    else if (key == GLFW_KEY_W && action == GLFW_RELEASE)
    {
        moveFront = 0;
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        moveFront = -1;
    }
    else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
    {
        moveFront = 0;
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        moveRight = 1;
    }
    else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
    {
        moveRight = 0;
    }
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        moveRight = -1;
    }
    else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
    {
        moveRight = 0;
    }
    if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
    {
        moveFront = moveFront*2;
    }
    else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE)
    {
        moveFront = moveFront / 2;
    }


    /////   JUMP
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        velocityY = 1;
    }

    /////   ESCAPE
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetInputMode(Window::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS && GLFW_CURSOR == GLFW_CURSOR_NORMAL)
    {
    }

}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        dash = 1;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        dash = 0;
    }
}

void cursor_enter_callback(GLFWwindow* window, int entered)
{
    if (entered)
    {
        mouse_button_callback;
    }
    else
    {
        // The cursor left the content area of the window
    }
}
#endif