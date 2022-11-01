#ifndef VERTEX_H
#define VERTEX_H

#include <glad/glad.h>
#include <vector>

class Vertex{
    GLuint *VAO;
    GLuint VAOSize;
public:
    explicit Vertex(GLuint VAOSize = 1);
    ~Vertex();
    Vertex(const Vertex &other) = delete;
    Vertex(const Vertex&& other) = delete;

    void initVAO(GLuint id = 0);
    void open(GLuint id = 0);
    void close();

    void setBuffer(const GLfloat* data, GLsizeiptr size, GLuint id = 0);
    void setIndex(const GLuint* data, GLsizeiptr size, GLuint id = 0);
    void setAttrib(GLuint index, GLint size, GLsizei stride, GLuint offset, GLuint id = 0);
};

#endif // VERTEX_H
