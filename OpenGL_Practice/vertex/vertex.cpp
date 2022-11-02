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

void Vertex::open(GLuint id) {
    glBindVertexArray(VAO[id]);
}

void Vertex::close() {
    glBindVertexArray(0);
}

void Vertex::setBuffer(const GLfloat* data, GLsizeiptr size, GLuint id) {
    this->open(id);
    GLuint bufferID;
    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    this->close();
}

void Vertex::setIndex(const GLuint* data, GLsizeiptr size, GLuint id) {
    this->open(id);
    GLuint indexID;
    glGenBuffers(1, &indexID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    this->close();
}

void Vertex::setAttrib(GLuint index, GLint size, GLsizei stride, GLuint offset, GLuint id) {
    this->open(id);
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(index);
    this->close();
}

