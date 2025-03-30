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


// Normalized Device Coordinates (NDC)
// viewport transforms these to screen-space coords.

float vertices[] = {
	0.25f, 0.75f, 0.0f,
	0.25f, 0.0f, 0.0f,
	0.0f, 0.75f, 0.0f,
	0.0f, 0.75f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.75f, -0.25f, 0.0f,
	0.75f, 0.0f, 0.0f,
	0.0f, -0.25f, 0.0f,
};

float first2tris[] = {
	0.25f, 0.0f, 0.0f,
	0.25f, 0.75f, 0.0f,
	0.0f, 0.75f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.25f, 0.0f, 0.0f,
	0.0f, 0.75f, 0.0f,
};

float second2tris[] = {
	0.0f, 0.0f, 0.0f,
	0.75f, -0.25f, 0.0f,
	0.75f, 0.0f, 0.0f,
	0.0f, -0.25f, 0.0f,
	0.75f, -0.25f, 0.0f,
	0.0f, 0.0f, 0.0f,
};

unsigned int topTris[] = {
	1, 0, 2, // tri1
	4, 1, 2, // tri2
	4, 5, 6, // tri3
	7, 5, 4 // tri4
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
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
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
	// Exercise: create 2 VAOs and VBOs at once.
	// unsigned int VBO, VAO, VBO_second, VAO_second;
	unsigned int VBO[2], VAO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);
	// FIRST VERTEX BUFFER STORED IN VERTEX ARRAY
	// -------------------------------------
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(first2tris), first2tris, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// -------------------------------------
	// SECOND VERTEX BUFFER STORED IN VERTEX ARRAY
	// -------------------------------------
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(second2tris), second2tris, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // we can use 0 in 5th argument
	// forcing opengl to attempt to resolve the stride size automatically.
	glEnableVertexAttribArray(0);
	// -------------------------------------

	// E L E M E N T  B U F F E R
	// -------------------------------------
	// -------------------------------------
	//unsigned int EBO;
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(topTris), topTris, GL_STATIC_DRAW);
	// -------------------------------------
	// -------------------------------------

	// C O N F I G U R E  V E R T E X  A T T R I B U T E S
	// -------------------------------------
	// -------------------------------------
	// operates on the GL_ARRAY_BUFFER target (currently VBO[0])
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
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
		glUseProgram(shaderProgram);
		//glUniform4f(vtxClrLoc, 0.0f, grnVal, 0.0f, 1.0f);
		// draw with first VAO
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// draw w second VAO
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0); // note this is a call to unbind
		
		// RENDER VERTICES STORED IN SECOND PAIR OF (VAO, VBO)
		//glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

		// check event loop and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	// free resources
	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	glDeleteProgram(shaderProgram);
	// E N D
	// -----------------------------------------------------------------------------
	// -----------------------------------------------------------------------------
	glfwTerminate();
	return 0;
	// -----------------------------------------------------------------------------
	// -----------------------------------------------------------------------------
}