#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../shader/shader.h"
#include "../vertex/vertex.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // Window Setup
    #pragma region
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    #pragma endregion

    // Shader
    VertexShader vertShader("shader/triangle_vs.glsl");
    FragmentShader fragShader("shader/triangle_fs.glsl");
    ShaderProgram ourShader(&vertShader, &fragShader);

    // Triangle
    float tri_1[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 

    };

    // Buffer
#pragma region
    Vertex vertex;
    vertex.initVAO();
    vertex.bind();
    vertex.setBuffer(tri_1, sizeof(tri_1));
    vertex.setAttrib(0, 3, 6 * sizeof(float), (void*)0);
    vertex.setAttrib(1, 3, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    vertex.release();
#pragma endregion

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        ourShader.use();
        
        vertex.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
