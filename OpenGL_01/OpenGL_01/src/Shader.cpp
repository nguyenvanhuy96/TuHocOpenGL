#include "Shader.h"
Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open the files
		vertexShaderFile.open(vertexPath);
		fragmentShaderFile.open(fragmentPath);
		// read the files
		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();
		// clode the files
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// read as strinf
		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();
	}
	catch (const std::exception&)
	{
		std::cout << "FAILED::FILES::TO_READ\n";
		glfwTerminate();
		return;
	}
	// read as const char
	vertexShaderData = vertexCode.c_str();
	fragmentShaderData = fragmentCode.c_str();
	// vertex
	this->vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->vertex, 1, &vertexShaderData, NULL);

	int success;
	char infolog[1024];
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 1024, NULL, infolog);
		std::cout << "FAILED::SHADER::VERTEX::<" << infolog << std::endl;
	}
	// fragment
	this->fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->fragment, 1, &fragmentShaderData, NULL);
	glGetShaderiv(this->fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(this->fragment, 1024, NULL, infolog);
		std::cout << "FAILED::SHADER::VERTEX::<" << infolog << std::endl;
	}
	// combine
	glCompileShader(this->vertex);
	glCompileShader(this->fragment);
	// program
	this->ID = glCreateProgram();
	glAttachShader(this->ID, this->vertex);
	glAttachShader(this->ID, this->fragment);
	glLinkProgram(this->ID);
	glGetShaderiv(this->ID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(this->ID, 1024, NULL, infolog);
		std::cout << "FAILED::SHADER::VERTEX::<" << infolog << std::endl;
	}
	glDeleteShader(this->vertex);
	glDeleteShader(this->fragment);
}

void Shader::use() {
	glUseProgram(this->ID);
}
void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}
