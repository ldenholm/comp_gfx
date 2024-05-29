#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Input.h"

using namespace std;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
	"vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\n\0";

const char* secondFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";

void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
};

float topTriVertices[] = {
	-0.5f, 0.0f, 0.0f, // centre left  0
	-0.5f, 0.5f, 0.0f, // top left  1
	0.0f, 0.5f, 0.0f, // centre top  2
	0.5f, 0.0f, 0.0f, // centre right  3
	0.5f, 0.5f, 0.0f // top right 4
};

unsigned int topTris[] = {
	0, 1, 2, // top left tri
	2, 4, 3, // top right tri
};

float botTriVertices[] = {
	-0.5f, -0.5f, 0.0f, // bot left 0
	0.5f, 0.5f, 0.0f, // bot right 1
	0.0f, 0.5f, 0.0f, // top mid 2
	0.0f, 0.0f, 0.0f, // origin 3
	-0.5f, 0.0f, 0.0f // centre left 4
};

float botTris[] = {
	0, 1, 2,
	0, 3, 4
};


unsigned int indices[] = {
	0, 1, 3, // first tri
	1, 2, 3 // second tri
};

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(800, 600, "HelloWindow", NULL, NULL);
	if (window == NULL)
	{
		cout << "Error creating window";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to init GLAD";
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// setup vertex buffer, element buffer, and shader objects
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); // VAO;
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check compile successful and capture logs.
	int success;
	char log[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, log);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log << endl;
	}
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check fragment shader compiled successfully
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, log);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << log << endl;
	}

	// compile second frag shader
	unsigned int secondFragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(secondFragShader, 1, &secondFragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, log);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << log << endl;
	}
	
	// init shader program
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check shader program attached & linked correctly
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, log);
		cout << "ERROR::PROGRAM::SHADER::COMPILATION_FAILED\n" << log << endl;
	}

	// clean up resources
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(secondFragShader);
	
	 /*
	 copy vertex data to buffer memory
	 the final argument instructs the gpu how to handle the data.
	 static draw corresponds to data set once and reused many times.
	 */

	// setup vertex array and buffer objects
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind vertex array then bind vertex buffers and finally config vertex attributes
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(topTriVertices), topTriVertices, GL_STATIC_DRAW);

	// SETUP EBO
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(topTris), topTris, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// CREATE SECOND VBO, VAO, EBO
	unsigned int VBO_SECOND, VAO_SECOND, EBO_SECOND;
	glGenVertexArrays(1, &VAO_SECOND);
	glGenBuffers(1, &VBO_SECOND);
	glBindVertexArray(VAO_SECOND);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_SECOND);
	glBufferData(GL_ARRAY_BUFFER, sizeof(botTriVertices), botTriVertices, GL_STATIC_DRAW);
	// SECOND EBO
	glGenBuffers(1, &EBO_SECOND);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_SECOND);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(botTris), botTris, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		// handle input
		Input::processInput(window);

		// renders commands here
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// draw triangle
		// dynamic coloring
		float time = glfwGetTime();
		float grnVal = (sin(time) / 2.0f) + 0.5f;
		int vtxClrLoc = glGetUniformLocation(shaderProgram, "ourColor");
		glUseProgram(shaderProgram);
		glUniform4f(vtxClrLoc, 0.0f, grnVal, 0.0f, 1.0f);
		glBindVertexArray(VAO);
		// draw multiple tris specified in element buffer
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		// RENDER VERTICES STORED IN SECOND PAIR OF (VAO, VBO)
		glBindVertexArray(VAO_SECOND);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// check event loop and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}