#include "shader/shader.h"
#include "shader/shaderProgram.h"

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

ShaderProgram::ShaderProgram(Shader* shader1, Shader* shader2) {
    ID = glCreateProgram();
    glAttachShader(ID, shader1->getID());
    glAttachShader(ID, shader2->getID());
    glLinkProgram(ID);

    int success{};
    char log_info[512];
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, nullptr, log_info);
        std::cout << "ERROR:SHADER::PROGRAM::LINK_FAILED\n" << log_info << std::endl;
    }
}

ShaderProgram::~ShaderProgram() {
    if (ID != 0) glDeleteProgram(ID);
}

void ShaderProgram::use() const noexcept {
    glUseProgram(ID);
}

void ShaderProgram::setBool(const std::string& name, bool value) const noexcept {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void ShaderProgram::setInt(const std::string& name, int value) const noexcept {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string& name, float value) const noexcept {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void ShaderProgram::setVec2(const std::string& name, const glm::vec2& value) const noexcept {
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void ShaderProgram::setVec2(const std::string& name, float x, float y) const noexcept {
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void ShaderProgram::setVec3(const std::string& name, const glm::vec3& value) const noexcept {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void ShaderProgram::setVec3(const std::string& name, float x, float y, float z) const noexcept {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void ShaderProgram::setVec4(const std::string& name, const glm::vec4& value) const noexcept {
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void ShaderProgram::setVec4(const std::string& name, float x, float y, float z, float w) const noexcept {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void ShaderProgram::setMat2(const std::string& name, const glm::mat2& mat) const noexcept {
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::setMat3(const std::string& name, const glm::mat3& mat) const noexcept {
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::setMat4(const std::string& name, const glm::mat4& mat) const noexcept {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}