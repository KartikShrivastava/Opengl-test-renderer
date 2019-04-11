//#include<iostream>
//#include<GL/glew.h>
//#include <GLFW/glfw3.h>
//#include<fstream>
//#include<string>
//#include<sstream>
//
//#define ASSERT(x) if(!(x)) __debugbreak();
//#define GLCall(x) GLClearError();\
//	x;\
//	ASSERT(GLLogError(#x, __FILE__, __LINE__))
//
//static void GLClearError() {
//	while (glGetError() != GL_NO_ERROR);
//}
//
//static bool GLLogError(const char* function, const char* file, int line) {
//	while (GLenum error = glGetError()) {
//		std::cout << "[OpenGL Error occured] : " << error << "\n" << function << "\n" << file << " : " << line << std::endl;
//		return false;
//	}
//	return true;
//}
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
//	GLCall(glShaderSource(id, 1, &source, NULL));
//	GLCall(glCompileShader(id));
//
//	//Error handling
//	int status;
//	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &status));
//	if (status == GL_FALSE) {
//		int length;
//		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
//		//char* message[length];	//this kind of allocation on stack is not possible, but... there is a way ;)
//		char* message = (char*)alloca(length * sizeof(char));
//		int len;
//		GLCall(glGetShaderInfoLog(id, length, &len, message));
//		std::cout << "Shader compilation failed for " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader.\n" << message << std::endl;
//		GLCall(glDeleteShader(id));
//		return 0;
//	}
//
//	return id;
//}
//
//static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
//	GLCall(unsigned int program = glCreateProgram());
//	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
//	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
//
//	GLCall(glAttachShader(program, vs));
//	GLCall(glAttachShader(program, fs));
//
//	GLCall(glLinkProgram(program));
//	GLCall(glValidateProgram(program));
//
//	GLCall(glDeleteShader(vs));
//	GLCall(glDetachShader(program, vs));
//	GLCall(glDeleteShader(fs));
//	GLCall(glDetachShader(program, fs));
//
//	return program;
//}
//
//
//int main()
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
//		 -0.5f, 0.5f
//	};
//
//	//NOTE: This is index buffer, it allows us to reuse repeated vertices
//	//Index buffer SHOULD BE of unsigned type, could be unsigned char, unsigned short, unsigned int
//	unsigned int indices[] = {
//		0,1,2,
//		2,3,0
//	};
//
//	unsigned int buffer;
//	GLCall(glGenBuffers(1, &buffer));
//	GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
//	GLCall(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW));
//	
//	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));
//	GLCall(glEnableVertexAttribArray(0));
//	
//	unsigned int ibo;
//	GLCall(glGenBuffers(1, &ibo));
//	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
//	GLCall(glNamedBufferData(ibo, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));	//this line sends the data to the GPU
//
//	ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
//
//	unsigned int shader = CreateShader(source.vertexShader, source.fragmentShader);
//	GLCall(glUseProgram(shader));
//
//	/* Loop until the user closes the window */
//	while (!glfwWindowShouldClose(window))
//	{
//		/* Render here */
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		//GLClearError();
//		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
//		//ASSERT(GLLogError());
//
//		/* Swap front and back buffers */
//		glfwSwapBuffers(window);
//
//		/* Poll for and process events */
//		glfwPollEvents();
//	}
//
//	GLCall(glDeleteProgram(shader));
//
//	glfwTerminate();
//	return 0;
//}