#pragma once

#include<string>
#include<unordered_map>

#include<glm/glm.hpp>

struct ShaderProgramSource {
	std::string vertexShader;
	std::string fragmentShader;
};

class Shader {
private:
	std::string m_FilePath;
	unsigned int m_RendererId;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filePath);
	~Shader();


	void Bind() const;
	void UnBind() const;

	//Set uniforms
	void SetUniform1i(const std::string & name, int value);
	void SetUniform1f(const std::string & name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, glm::mat4 mvpMat);

private:
	ShaderProgramSource ParseShader(const std::string& filePath);
	unsigned int CompileShader(unsigned int type, const std::string & shader);
	unsigned int CreateShader(const std::string & vertexShader, const std::string & fragmentShader);

	int GetUniformLocation(const std::string& name);
};