#include "window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

Window::Window(int major, int minor) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
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

void Window::init(int width, int height, const char* title) {
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

void Window::setup(std::vector<SETTINGS> settings) {
    for (auto& setting : settings) {
        switch (setting) {
            case SETTINGS::BLEND:
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glEnable(GL_BLEND);
                break;
            case SETTINGS::LINE_SMOOTH:
                glEnable(GL_LINE_SMOOTH);
                break;
            case SETTINGS::DEPTH_TEST:
                glEnable(GL_DEPTH_TEST);
                break;
            case SETTINGS::POINT_SIZE:
                glEnable(GL_PROGRAM_POINT_SIZE);
                break;
            case SETTINGS::CULL_FACE:
                glEnable(GL_CULL_FACE);
                break;
            case SETTINGS::MULTISAMPLE:
                glEnable(GL_MULTISAMPLE);
                break;
            default: break;
        }
    }
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

void Window::close() {
    glfwSetWindowShouldClose(window, true);
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}