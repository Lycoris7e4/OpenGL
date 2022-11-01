#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <glm/glm.hpp>
#include <string>

class Shader;

class ShaderProgram {
public:
    unsigned int ID;
    ShaderProgram(Shader* shader1, Shader* shader2);

    ~ShaderProgram();

    void use() const noexcept;

    void setBool(const std::string& name, bool value) const noexcept;
    void setInt(const std::string& name, int value) const noexcept;
    void setFloat(const std::string& name, float value) const noexcept;

    void setVec2(const std::string& name, const glm::vec2& value) const noexcept;
    void setVec2(const std::string& name, float x, float y) const noexcept;

    void setVec3(const std::string& name, const glm::vec3& value) const noexcept;
    void setVec3(const std::string& name, float x, float y, float z) const noexcept;

    void setVec4(const std::string& name, const glm::vec4& value) const noexcept;
    void setVec4(const std::string& name, float x, float y, float z, float w) const noexcept;

    void setMat2(const std::string& name, const glm::mat2& mat) const noexcept;
    void setMat3(const std::string& name, const glm::mat3& mat) const noexcept;
    void setMat4(const std::string& name, const glm::mat4& mat) const noexcept;
};

#endif // SHADER_PROGRAM_H
