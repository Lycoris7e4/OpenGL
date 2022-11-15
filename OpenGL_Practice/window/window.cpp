#include "window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

Window::Window() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Window::~Window() {}

GLFWwindow* Window::getWindow() {
    return window;
}

float Window::getWidth() {
    return static_cast<float>(SCR_WIDTH);
}

float Window::getHeight() {
    return static_cast<float>(SCR_HEIGHT);
}

void Window::setup(int width, int height, const char* title) {
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL) {
        this->terminate();
        throw new ERROR::WINDOWCREATION;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int w, int h) {
        glViewport(0, 0, w, h);
    });

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw new ERROR::GLADINIT;
    }

    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

void Window::update() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::terminate() {
    glfwTerminate();
}

void Window::setCursor(void (*callback)(GLFWwindow* window, double xpos, double ypos)) {
    glfwSetCursorPosCallback(window, callback);
}

void Window::setScroll(void (*callback)(GLFWwindow* window, double xoffset, double yoffset)) {
    glfwSetScrollCallback(window, callback);
}

void Window::disableCursor() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::setDepthTest() {
    glEnable(GL_DEPTH_TEST);
}

void Window::close() {
    glfwSetWindowShouldClose(window, true);
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}