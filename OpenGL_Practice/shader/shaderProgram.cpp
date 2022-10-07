#include <glad/glad.h>
#include <iostream>

#include "shader.h"
#include "shaderProgram.h"

ShaderProgram::ShaderProgram(Shader* shader1, Shader* shader2): ID{0} {
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

ShaderProgram::~ShaderProgram(){
	if (ID != 0)
		glDeleteProgram(ID);
}

void ShaderProgram::use() const noexcept{
	glUseProgram(ID);
}

void ShaderProgram::setUniform(const std::string& name, bool value) const noexcept {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<int>(value));
}

void ShaderProgram::setUniform(const std::string& name, int value) const noexcept {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void ShaderProgram::setUniform(const std::string& name, float value) const noexcept {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void ShaderProgram::setUniform(const std::string& name, GLsizei numMatrix, int isTranspose, float* value) const noexcept {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), numMatrix, isTranspose, value);
}