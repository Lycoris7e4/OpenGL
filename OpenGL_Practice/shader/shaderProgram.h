#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <string>

class Shader;

class ShaderProgram {
public:
	ShaderProgram(Shader* shader1, Shader* shader2);
	~ShaderProgram();

	void use() const noexcept;

	void setUniform(const std::string& name, bool value) const noexcept;
	void setUniform(const std::string& name, int value) const noexcept;
	void setUniform(const std::string& name, float value) const noexcept;
	void setUniform(const std::string& name, GLsizei numMatrix, int isTranspose, float* value) const noexcept;

private:
	unsigned ID;
};

#endif
