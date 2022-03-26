#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	unsigned int ID;
	void use();
	// utility uniforms
	void setFloat(const std::string& name, float value) const;
	void setInt(const std::string& name, int value) const;

private:
	std::string vertexCode, fragmentCode;
	std::ifstream vertexShaderFile, fragmentShaderFile;
	const char* vertexShaderData, * fragmentShaderData;
	unsigned int vertex, fragment;
	std::stringstream vertexShaderStream, fragmentShaderStream;
};
