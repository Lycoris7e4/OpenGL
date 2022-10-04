#include <glad/glad.h>
#include <iostream>

#include "shader.h"
#include "shaderProgram.h"

template<class Shader1, class Shader2>
ShaderProgram<class Shader1, class Shader2>::ShaderProgram(Shader1 shader1, Shader2 shader2): ID{0} {

	ID = glCreateProgram();
	glAttachShader(ID, shader1.getID());
	glAttachShader(ID, shader2.getID());
	glLinkProgram(ID);

	int success{};
	char log_info[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, nullptr, log_info);
		std::cout << "ERROR:SHADER::PROGRAM::LINK_FAILED\n" << log_info << std::endl;
	}
}

template<class Shader1, class Shader2>
ShaderProgram<class Shader1, class Shader2>::~ShaderProgram()
{
	if (ID != 0)
		glDeleteProgram(ID);
}

template<class Shader1, class Shader2>
void ShaderProgram<class Shader1, class Shader2>::setUniform(std::string name, bool value) const noexcept
{
	glUniform1i(glGetUniformLocation(ID, name.data()), static_cast<int>(value));
}

template<class Shader1, class Shader2>
void ShaderProgram<class Shader1, class Shader2>::setUniform(std::string name, int value) const noexcept
{
	glUniform1i(glGetUniformLocation(ID, name.data()), value);
}

template<class Shader1, class Shader2>
void ShaderProgram<class Shader1, class Shader2>::setUniform(std::string name, float value) const noexcept
{
	glUniform1f(glGetUniformLocation(ID, name.data()), value);
}

template<class Shader1, class Shader2>
void ShaderProgram<class Shader1, class Shader2>::use() const noexcept
{
	glUseProgram(ID);
}