#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "../shader/shader.h"
#include "../camera/camera.h"
#include "../window/window.h"
#include "../vertex/vertex.h"

void processInput(Window* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

Camera camera(glm::vec3(0.779634f, 1.99844f, -1.52823f), glm::vec3(0, 1, 0), -19.9997f, -5.59997f);
float lastX;
float lastY;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {
    // Window
#pragma region
    Window* window = new Window();
    try {
        window->init(800, 600, "Arch Model");
    } 
    catch (ERROR::GLADINIT) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    catch (ERROR::WINDOWCREATION) {
        std::cout << "Failed to create window" << std::endl;
        return -1;
    }

    window->setCursor(mouse_callback);
    window->setScroll(scroll_callback);
    window->disableCursor();

    window->setup({SETTINGS::BLEND, SETTINGS::DEPTH_TEST, SETTINGS::MULTISAMPLE});
#pragma endregion

    // Camera
    lastX = window->getWidth() / 2.0f;
    lastY = window->getHeight() / 2.0f;

    // Shader
    ShaderProgram shader(new VertexShader("shader/arch_vs.glsl"), 
                         new GeometryShader("shader/arch_gs.glsl"),
                         new FragmentShader("shader/arch_fs.glsl"));
    shader.use();

    // Line (Top Line of the Arch)
    float vertices[] = {
        2.0f, 2.0f, -2.0f,
        4.0f, 2.0f, -2.0f,
        6.0f, 1.5f, -2.0f,
        8.0f, 2.0f, -2.0f
    };

    Vertex vertex;
    vertex.initVAO();
    vertex.bind();
    vertex.setBuffer(vertices, sizeof(vertices));
    vertex.setAttrib(0, 3, 3 * sizeof(float), nullptr);
    vertex.release();

    // Rendering
    while (!window->shouldClose()) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), window->getWidth() / window->getHeight(), 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 mvp = projection * view * model;

        shader.setMat4("mvp", mvp);
        shader.setFloat("radius", 0.1f);
        shader.setVec4("color", 1.0f, 1.0f, 0.0f, 1.0f);

        vertex.bind();
        glDrawArrays(GL_LINE_STRIP, 0, 3);
        vertex.release();

        window->update();
    }

    window->terminate();
    return 0;
}

void processInput(Window* window) {
    GLFWwindow* w = window->getWindow();
    if (glfwGetKey(w, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(w, true);

    if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime * 0.5);
    if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime * 0.5);
    if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime * 0.5);
    if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime * 0.5);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}