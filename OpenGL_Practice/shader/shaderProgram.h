#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader;

class ShaderProgram {
public:
    unsigned int ID;
    ShaderProgram(Shader* shader1, Shader* shader2) {
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

    ~ShaderProgram() {
        if (ID != 0) glDeleteProgram(ID);
    }

    void use() const noexcept {
        glUseProgram(ID);
    }

    void setBool(const std::string& name, bool value) const noexcept {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    void setInt(const std::string& name, int value) const noexcept {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setFloat(const std::string& name, float value) const noexcept {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setVec2(const std::string& name, const glm::vec2& value) const noexcept {
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void setVec2(const std::string& name, float x, float y) const noexcept {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }

    void setVec3(const std::string& name, const glm::vec3& value) const noexcept {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void setVec3(const std::string& name, float x, float y, float z) const noexcept {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }

    void setVec4(const std::string& name, const glm::vec4& value) const noexcept {
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void setVec4(const std::string& name, float x, float y, float z, float w) const noexcept {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }

    void setMat2(const std::string& name, const glm::mat2& mat) const noexcept {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat3(const std::string& name, const glm::mat3& mat) const noexcept {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat4(const std::string& name, const glm::mat4& mat) const noexcept {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
};

#endif
