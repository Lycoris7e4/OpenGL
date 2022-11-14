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

Window::~Window() {

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

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::processInput() {
    //float currentFrame = static_cast<float>(glfwGetTime());
    //deltaTime = currentFrame - lastFrame;
    //lastFrame = currentFrame;
    //if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    //    glfwSetWindowShouldClose(window, true);

    //if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    //    camera.ProcessKeyboard(FORWARD, deltaTime);
    //if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    //    camera.ProcessKeyboard(BACKWARD, deltaTime);
    //if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    //    camera.ProcessKeyboard(LEFT, deltaTime);
    //if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    //    camera.ProcessKeyboard(RIGHT, deltaTime);
}

void Window::setCursor() {
    // glfwSetCursorPosCallback(window, mouse_callback);
}

void Window::setScroll() {
    // glfwSetScrollCallback(window, scroll_callback);
}

void Window::disableCursor() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::setDepthTest() {
    glEnable(GL_DEPTH_TEST);
}