//#include<iostream>
//#include<GL/glew.h>
//#include <GLFW/glfw3.h>
//#include<fstream>
//#include<string>
//#include<sstream>
//
//#include<utility>
//#include<tuple>
//
//struct ShaderProgramSource {
//	std::string vertexShader;
//	std::string fragmentShader;
//};
//
//static ShaderProgramSource ParseShader(const std::string& filePath) {
//	enum class ShaderType {
//		NONE = -1, VERTEX = 0, FRAGMENT = 1
//	};
//
//	ShaderType type = ShaderType::NONE;
//
//	std::ifstream stream(filePath);
//	std::stringstream ss[2];
//
//	std::string line;
//	while (getline(stream, line)) {
//		if (line.find("#shader") != std::string::npos) {
//			if (line.find("vertex") != std::string::npos) //set mode to vertex
//				type = ShaderType::VERTEX;
//			if (line.find("fragment") != std::string::npos) //set mode to fragment
//				type = ShaderType::FRAGMENT;
//		}
//		else {
//			ss[(int)type] << line << std::endl;
//		}
//	}
//
//	return { ss[0].str(),ss[1].str() };
//}
//
//static unsigned int CompileShader(unsigned int type, const std::string& shader) {
//	unsigned int id = glCreateShader(type);
//	const char* source = shader.c_str();
//	glShaderSource(id, 1, &source, NULL);
//	glCompileShader(id);
//
//	//Error handling
//	int status;
//	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
//	if (status == GL_FALSE) {
//		int length;
//		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
//		//char* message[length];	//this kind of allocation on stack is not possible, but... there is a way ;)
//		char* message = (char*)alloca(length * sizeof(char));
//		int len;
//		glGetShaderInfoLog(id, length, &len, message);
//		std::cout << "Shader compilation failed for " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader.\n" << message << std::endl;
//		glDeleteShader(id);
//		return 0;
//	}
//
//	return id;
//}
//
//static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
//	unsigned int program = glCreateProgram();
//	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
//	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
//
//	glAttachShader(program, vs);
//	glAttachShader(program, fs);
//
//	glLinkProgram(program);
//	glValidateProgram(program);
//
//	glDeleteShader(vs);
//	glDetachShader(program, vs);
//	glDeleteShader(fs);
//	glDetachShader(program, fs);
//
//	return program;
//}
//
//
//int mainn()
//{
//	GLFWwindow* window;
//
//	/* Initialize the library */
//	if (!glfwInit())
//		return -1;
//
//	/* Create a windowed mode window and its OpenGL context */
//	window = glfwCreateWindow(400, 400, "Hello World", NULL, NULL);
//	if (!window)
//	{
//		glfwTerminate();
//		return -1;
//	}
//
//	/* Make the window's context current */
//	glfwMakeContextCurrent(window);
//
//	GLenum status = glewInit();
//	if (status != GLEW_OK) {
//		std::cout << "it fails man" << std::endl;
//	}
//
//	float positions[] = {
//		 -0.5f,-0.5f,
//		  0.5f,-0.5f,
//		  0.5f, 0.5f,
//
//		  0.5f, 0.5f,
//		 -0.5f, 0.5f,
//		 -0.5f,-0.5f
//	};
//
//	unsigned int buffer;
//	glGenBuffers(1, &buffer);
//	glBindBuffer(GL_ARRAY_BUFFER, buffer);
//	glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
//	glEnableVertexAttribArray(0);
//
//	ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
//
//	unsigned int shader = CreateShader(source.vertexShader, source.fragmentShader);
//	glUseProgram(shader);
//
//	/* Loop until the user closes the window */
//	while (!glfwWindowShouldClose(window))
//	{
//		/* Render here */
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		glDrawArrays(GL_TRIANGLES, 0, 3 * 2);
//
//		/* Swap front and back buffers */
//		glfwSwapBuffers(window);
//
//		/* Poll for and process events */
//		glfwPollEvents();
//	}
//
//	glDeleteProgram(shader);
//
//	glfwTerminate();
//	return 0;
//}