#pragma once
#include "pch.h"

class Shader
{
private:
	unsigned int id;
	std::string filePath;

public:
	Shader(const std::string&);
	~Shader();

	void Bind() const;
	void Unbind() const;

	int GetUniformLocation(const std::string& name);

	// Set Uniforms
	void SetUniform4f(const std::string& name, glm::vec4);

private:
	unsigned int CompileShader(const std::string& source, unsigned int type);
	unsigned int CreateShader(const std::string& VertexShader, const std::string& FragmentShader);
};