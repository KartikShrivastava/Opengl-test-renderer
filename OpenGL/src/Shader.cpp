#include"Shader.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include "Renderer.h"

Shader::Shader(const std::string & filePath) : m_FilePath(filePath),m_RendererId(0)
{
	ShaderProgramSource source = ParseShader(filePath);
	m_RendererId = CreateShader(source.vertexShader, source.fragmentShader);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererId));
}

ShaderProgramSource Shader::ParseShader(const std::string& filePath) {
	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	ShaderType type = ShaderType::NONE;

	std::ifstream stream(filePath);
	std::stringstream ss[2];

	std::string line;
	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) //set mode to vertex
				type = ShaderType::VERTEX;
			if (line.find("fragment") != std::string::npos) //set mode to fragment
				type = ShaderType::FRAGMENT;
		}
		else {
			ss[(int)type] << line << std::endl;
		}
	}

	return { ss[0].str(),ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& shader) {
	unsigned int id = glCreateShader(type);
	const char* source = shader.c_str();
	GLCall(glShaderSource(id, 1, &source, NULL));
	GLCall(glCompileShader(id));

	//Error handling
	int status;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &status));
	if (status == GL_FALSE) {
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		//char* message[length];	//this kind of allocation on stack is not possible, but... there is a way ;)
		char* message = (char*)alloca(length * sizeof(char));
		int len;
		GLCall(glGetShaderInfoLog(id, length, &len, message));
		std::cout << "Shader compilation failed for " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader.\n" << message << std::endl;
		GLCall(glDeleteShader(id));
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
	GLCall(unsigned int program = glCreateProgram());
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

   	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));

	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDetachShader(program, vs));
	GLCall(glDeleteShader(fs));
	GLCall(glDetachShader(program, fs));

	return program;
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererId));
}

void Shader::UnBind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string & name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string & name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string & name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}


void Shader::SetUniformMat4f(const std::string & name, glm::mat4 mvpMat)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mvpMat[0][0]));
}

int Shader::GetUniformLocation(const std::string & name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_RendererId, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	m_UniformLocationCache[name] = location;

	return location;
}