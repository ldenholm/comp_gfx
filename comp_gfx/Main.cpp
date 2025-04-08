#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Input.h"
#include "Shaders.h"
#include "Transformations.h"
#include "glm/glm.hpp"


void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

void color_cycle_green(unsigned int& shaderProgram)
{
	float t = glfwGetTime();
	float green = (sin(2*t) / 2.0f) + 0.5f;
	int vertexColorLoc = glGetUniformLocation(shaderProgram, "dynamicColor");
	glUseProgram(shaderProgram);
	glUniform4f(vertexColorLoc, 0.0f, green, 0.0f, 1.0f);
}

void color_cycle_red(unsigned int& shaderProgram)
{
	float t = glfwGetTime();
	float freq = (sin(3.0f*t) / 1.0f) + 0.2f;
	int vertexColorLoc = glGetUniformLocation(shaderProgram, "dynamicColor");
	glUseProgram(shaderProgram);
	glUniform4f(vertexColorLoc, (freq + 0.1f), (freq - 0.6f), (freq - 0.9f), 0.4f);
}

// Normalized Device Coordinates (NDC)
// viewport transforms these to screen-space coords.

float vertices[] = 
{
	0.25f, 0.75f, 0.0f,
	0.25f, 0.0f, 0.0f,
	0.0f, 0.75f, 0.0f,
	0.0f, 0.75f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.75f, -0.25f, 0.0f,
	0.75f, 0.0f, 0.0f,
	0.0f, -0.25f, 0.0f,
};

float first2tris[] = 
{
	0.25f, 0.0f, 0.0f,
	0.25f, 0.75f, 0.0f,
	0.0f, 0.75f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.25f, 0.0f, 0.0f,
	0.0f, 0.75f, 0.0f,
};

float second2tris[] = 
{
	0.0f, 0.0f, 0.0f,
	0.75f, -0.25f, 0.0f,
	0.75f, 0.0f, 0.0f,
	0.0f, -0.25f, 0.0f,
	0.75f, -0.25f, 0.0f,
	0.0f, 0.0f, 0.0f,
};

unsigned int topTris[] = 
{
	1, 0, 2, // tri1
	4, 1, 2, // tri2
	4, 5, 6, // tri3
	7, 5, 4 // tri4
};

int main() 
{
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
	
	// S H A D E R  C O M P I L E  A N D  P R O G R A M  S E T U P
	// -----------------------------------------------------------------------------
	// -----------------------------------------------------------------------------
	GLuint vertexShader, fragShader;
	Shaders::compile_and_create_shader(GL_VERTEX_SHADER, "VertexIO.vs.glsl", vertexShader);
	Shaders::compile_and_create_shader(GL_FRAGMENT_SHADER, "FRAGIO.fs.glsl", fragShader);
	//Shaders::compile_and_create_shader(GL_VERTEX_SHADER, "Translator.vs.glsl", transShader);
	std::vector<GLuint> shaders;
	shaders.push_back(vertexShader);
	shaders.push_back(fragShader);
	//shaders.push_back(transShader);
	GLuint shaderProg = Shaders::create_and_link_shader_program(shaders);

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

	color_cycle_green(shaderProg);

	// draw with first VAO
	glBindVertexArray(VAO[0]);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	color_cycle_red(shaderProg);
		

	// draw w second VAO
	glBindVertexArray(VAO[1]);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Transformations::translate(shaderProg);
	// one takes precedence, need to properly implement transformation combinations
	Transformations::rotate(shaderProg);
	glBindVertexArray(0); // note this is a call to unbind
		

	// check event loop and swap buffers
	glfwSwapBuffers(window);
	glfwPollEvents();

	}

	// free resources
	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	glDeleteProgram(shaderProg);
	// E N D
	// -----------------------------------------------------------------------------
	// -----------------------------------------------------------------------------
	glfwTerminate();
	return 0;
}