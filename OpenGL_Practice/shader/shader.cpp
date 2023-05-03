#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "shader.h"

Shader::Shader(std::string file_path): ID{0} {
	std::ifstream fs{};
	fs.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		fs.open(std::string{file_path});
		std::stringstream ss{};
		ss << fs.rdbuf();
		fs.close();
		source = ss.str();
	} catch (std::ifstream::failure e) {
		std::cout << "Error::Shader::File_Not_Successfully_Read" << std::endl;
	}
}

Shader::~Shader() {
	if (ID != 0) {
		glDeleteShader(ID);
	}
}

VertexShader::VertexShader(std::string file_path): Shader{file_path} {
	ID = glCreateShader(GL_VERTEX_SHADER);
	auto sourceStr = source.c_str();
	glShaderSource(ID, 1, &sourceStr, nullptr);
	glCompileShader(ID);

	int success{};
	char log[512];
	glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(ID, 512, nullptr, log);
		std::cout << "ERROR:SHADER::VERTEX::COMPILEATION_FAILED\n" << log << std::endl;
	}
}

FragmentShader::FragmentShader(std::string file_path): Shader{file_path} {
	ID = glCreateShader(GL_FRAGMENT_SHADER);
	auto sourceStr = source.c_str();
	glShaderSource(ID, 1, &sourceStr, nullptr);
	glCompileShader(ID);

	int success{};
	char log[512];
	glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(ID, 512, nullptr, log);
		std::cout << "ERROR:SHADER::FRAGMENT::COMPILEATION_FAILED\n" << log << std::endl;
	}
}

GeometryShader::GeometryShader(std::string file_path) : Shader{ file_path } {
	ID = glCreateShader(GL_GEOMETRY_SHADER);
	auto sourceStr = source.c_str();
	glShaderSource(ID, 1, &sourceStr, nullptr);
	glCompileShader(ID);

	int success{};
	char log[512];
	glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(ID, 512, nullptr, log);
		std::cout << "ERROR:SHADER::GEOMETRY::COMPILEATION_FAILED\n" << log << std::endl;
	}
}
