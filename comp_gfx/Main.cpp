#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Input.h"
#include "Shaders.h"
#include "Transformations.h"
#include "glm/glm.hpp"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Mesh.h"
#include "Model.h"
#include "filesystem"


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

float cube_vertices[] =
{
	0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f
};

//float first2tris[] = 
//{
//	0.25f, 0.0f, 0.0f,
//	0.25f, 0.75f, 0.0f,
//	0.0f, 0.75f, 0.0f,
//	0.0f, 0.0f, 0.0f,
//	0.25f, 0.0f, 0.0f,
//	0.0f, 0.75f, 0.0f,
//};
//
//float second2tris[] = 
//{
//	0.0f, 0.0f, 0.0f,
//	0.75f, -0.25f, 0.0f,
//	0.75f, 0.0f, 0.0f,
//	0.0f, -0.25f, 0.0f,
//	0.75f, -0.25f, 0.0f,
//	0.0f, 0.0f, 0.0f,
//};

unsigned int cube_indices[] = 
{
	0, 1, 2,
	1, 3, 4,
	5, 6, 3,
	7, 3, 6,
	2, 4, 7,
	0, 7, 6,
	0, 5, 1,
	1, 5, 3,
	5, 0, 6,
	7, 4, 3,
	2, 1, 4,
	0, 2, 7
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
	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CW);
	//glCullFace(GL_BACK);
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

	// V E R T E X  B U F F E R
	// -------------------------------------
	// -------------------------------------
	/*unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);*/
	// -------------------------------------
	// -------------------------------------

	// I N D E X  B U F F E R
	// -------------------------------------
	// -------------------------------------

	
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	//glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);


	// L O A D  M O D E L
	Model model("blender/Projeto.obj");

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
		glUseProgram(shaderProg);
		model.Draw();
		//Transformations::scale(shaderProg, 0.001f, 1.2f);
		//Transformations::scaleByX(shaderProg, 0.2f);
		Transformations::projection(shaderProg);

		color_cycle_green(shaderProg);

		//color_cycle_green(shaderProg);

		//glBindVertexArray(VAO);	
		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		//Transformations::projection(shaderProg);
		//Transformations::identity(shaderProg);

		//color_cycle_red(shaderProg);

		//Transformations::translate(shaderProg);
		// one takes precedence, need to properly implement transformation combinations
		//Transformations::rotate_x(shaderProg);
		//Transformations::scale(shaderProg, 0.001f, 1.2f);
		//Transformations::s_r_t(shaderProg);
		//Transformations::identity(shaderProg);
		//Transformations::rotate_y(shaderProg);

		// check event loop and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	// free resources
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProg);
	// E N D
	// -----------------------------------------------------------------------------
	// -----------------------------------------------------------------------------
	glfwTerminate();
	return 0;
}