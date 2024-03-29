#include "vertex.h"
#include <GLFW/glfw3.h>

Vertex::Vertex(GLuint VAOSize): VAOSize(VAOSize) {
    VAO = new GLuint[VAOSize];
}

Vertex::~Vertex() {
    delete VAO;
}

void Vertex::initVAO(GLuint id) {
    if (id < VAOSize) {
        glGenVertexArrays(1, VAO + id);
    }
    else {
        throw;
    }
}

GLuint& Vertex::getVAO(GLuint id) {
    if (id < VAOSize) {
        return VAO[id];
    }
    else {
        throw;
    }
}

void Vertex::bind(GLuint id) {
    glBindVertexArray(VAO[id]);
}

void Vertex::release() {
    glBindVertexArray(0);
}

void Vertex::setBuffer(const void* data, GLsizeiptr size, GLuint id) {
    GLuint bufferID;
    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void Vertex::setIndex(const GLuint* data, GLsizeiptr size, GLuint id) {
    GLuint indexID;
    glGenBuffers(1, &indexID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void Vertex::setAttrib(GLuint index, GLint size, GLsizei stride, const void* pointer, GLuint id) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, pointer);
}

void Vertex::setAttribI(GLuint index, GLint size, GLsizei stride, const void* pointer, GLuint id) {
    glEnableVertexAttribArray(index);
    glVertexAttribIPointer(index, size, GL_INT, stride, pointer);
}

