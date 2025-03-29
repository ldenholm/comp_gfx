#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Input.h"

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
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

//float topTriVertices[] = {
//	// positions       // colors
//	-0.5f, 0.0f, 0.0f,  // centre left  0
//	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // top left  1
//	0.0f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f, // centre top  2
//	0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // centre right  3
//	0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top right 4
//};


// Normalized Device Coordinates (NDC)
// viewport transforms these to screen-space coords.
float vertices[] = {
	-0.5f, -0.5f, 0.0f, // left bot
	 0.5f, -0.5f, 0.0f, // right bot
	 0.0f,  0.5f, 0.0f // centre top
};


unsigned int topTris[] = {
	0, 1, 2, // top left tri
	2, 4, 3, // top right tri
};


int main() {

	std::cout << "this is the char* shader source w comments in both: \n" << vertexShaderSource << std::endl << fragmentShaderSource << std::endl;

	// I N I T  A N D  W I N D O W  S E T U P
	// -----------------------------------------------------------------------------
	// -----------------------------------------------------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(800, 600, "HelloWindow", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Error creating window";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init GLAD";
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// -----------------------------------------------------------------------------
	// -----------------------------------------------------------------------------

	// V E R T E X  S H A D E R  C O M P I L E//
	// -----------------------------------------------------------------------------
	// -----------------------------------------------------------------------------
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
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log << std::endl;
	}
	// -----------------------------------------------------------------------------
	// -----------------------------------------------------------------------------

	// F R A G M E N T  S H A D E R  C O M P I L E//
	// -----------------------------------------------------------------------------
	// -----------------------------------------------------------------------------
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	
	// check fragment shader compiled successfully
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << log << std::endl;
	}
	// -----------------------------------------------------------------------------
	// -----------------------------------------------------------------------------
	
	
	// S H A D E R  P R O G R A M  S E T U P
	// -----------------------------------------------------------------------------
	// -----------------------------------------------------------------------------
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	
	// check shader program attached & linked correctly
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, log);
		std::cout << "ERROR::PROGRAM::SHADER::COMPILATION_FAILED\n" << log << std::endl;
	}

	// clean up resources
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// -----------------------------------------------------------------------------
	// -----------------------------------------------------------------------------
	
	// B U F F E R  O B J E C T S  S E T U P
	// -----------------------------------------------------------------------------
	// -----------------------------------------------------------------------------

	 /*
	 copy vertex data to buffer memory
	 the final argument instructs the gpu how to handle the data.
	 static draw corresponds to data set once and reused many times.
	 */

	// V E R T E X  B U F F E R
	// -------------------------------------
	// -------------------------------------
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// -------------------------------------
	// -------------------------------------

	// E L E M E N T  B U F F E R
	// -------------------------------------
	// -------------------------------------
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(topTris), topTris, GL_STATIC_DRAW);
	// -------------------------------------
	// -------------------------------------

	// C O N F I G U R E  V E R T E X  A T T R I B U T E S
	// -------------------------------------
	// -------------------------------------
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(1);

	// R E N D E R I N G
	// -----------------------------------------------------------------------------
	// -----------------------------------------------------------------------------
	while (!glfwWindowShouldClose(window))
	{
		// handle input
		Input::processInput(window);

		// renders commands here
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// draw triangle
		// dynamic coloring
		//float time = glfwGetTime();
		//float grnVal = (sin(time) / 2.0f) + 0.5f;
		//int vtxClrLoc = glGetUniformLocation(shaderProgram, "ourColor");
		glUseProgram(shaderProgram);
		//glUniform4f(vtxClrLoc, 0.0f, grnVal, 0.0f, 1.0f);
		glBindVertexArray(VAO);
		// draw multiple tris specified in element buffer
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		// RENDER VERTICES STORED IN SECOND PAIR OF (VAO, VBO)
		//glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);

		// check event loop and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// -----------------------------------------------------------------------------
	// -----------------------------------------------------------------------------

	// E N D
	// -----------------------------------------------------------------------------
	// -----------------------------------------------------------------------------
	glfwTerminate();
	return 0;
	// -----------------------------------------------------------------------------
	// -----------------------------------------------------------------------------
}