#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <string>

template<class Shader1, class Shader2>
class ShaderProgram {
public:
	ShaderProgram(Shader1 shader1, Shader2 shader2);
	~ShaderProgram();

	void use() const noexcept;

	void setUniform(std::string name, bool value) const noexcept;
	void setUniform(std::string name, int value) const noexcept;
	void setUniform(std::string name, float value) const noexcept;

private:
	unsigned ID;
};

#endif
