#ifndef SHADER_H
#define SHADER_H

#include <string>

class Shader {
public:
	explicit Shader(std::string file_path);
	~Shader();

	virtual unsigned getID() const noexcept { return ID; }

protected:
	unsigned ID;

	std::string source;
};

class VertexShader : public Shader {
public:
	explicit VertexShader(std::string file_path);
};

class FragmentShader : public Shader {
public:
	explicit FragmentShader(std::string file_path);
};

#endif
