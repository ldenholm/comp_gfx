#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Input.h"

using namespace std;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
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

float myTestTri[] = {
	-0.5f, 0.0f, 0.0f, // centre left  0
	-0.5f, 0.5f, 0.0f, // top left  1
	0.0f, 0.5f, 0.0f, // centre top  2
	0.5f, 0.0f, 0.0f, // centre right  3
	0.5f, 0.5f, 0.0f // top right 4
	-0.5f, -0.5f, 0.0f, // bottom left 5
	0.0f, -0.5f, 0.0f, // centre bottom 6
	0.5f, -0.5f, 0.0f // bottom right 7
	-0.25f, 0.25f, 0.0f // half left half top
};

unsigned int squareTri[] = {
	0, 1, 2, // top left tri
	2, 4, 3, // top right tri
	0, 5, 6, // bot left tri
	3, 7, 6 // bot right tri
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

	// create element buffer obj
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(myTestTri), myTestTri, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareTri), squareTri, GL_STATIC_DRAW);
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
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		// draw multiple tris specified in element buffer
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// check event loop and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}