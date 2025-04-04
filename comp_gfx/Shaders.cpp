#include "Shaders.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>


// // todo generalize this for use with geometry and fragment shaders
// Reads shader from file, compiles shader, links 

GLuint Shaders::Shaders::compile_and_create_shader(GLenum shaderType, const char* shaderSrcPath, GLuint& shader)
{
	std::cout << "provided path: " << shaderSrcPath << std::endl;
	std::ifstream infile{ shaderSrcPath };
	if (infile)
	{
		std::ostringstream sstream;
		std::string line, src;
		
		sstream << infile.rdbuf();
		std::cout << infile.rdbuf();
		const std::string str(sstream.str());
		const char* src_ptr = str.c_str();

		//while (std::getline(infile, line))
		//{
		//	src += line += "\n";
		//	std::cout << line << std::endl;
		//}

		shader = glCreateShader(shaderType);
		glShaderSource(shader, 1, &src_ptr, NULL);
		glCompileShader(shader);

		// check compile successful and capture logs.
		char log[512];
		int success = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, log);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log << std::endl;
			return success;
		}
	}
	else
	{
		std::cout << "Error reading shader source file" << std::endl;
	}
	return shader;
}

GLuint Shaders::Shaders::create_and_link_shader_program(std::vector<GLuint>& shaders)
{
	int success = 0;
	char log[512];
	GLuint shaderProgram = glCreateProgram();
	
	for (auto& shader : shaders)
	{
		glAttachShader(shaderProgram, shader);
	}

	glLinkProgram(shaderProgram);
	// check shader program attached & linked correctly
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, log);
		std::cout << "ERROR::PROGRAM::SHADER::COMPILATION_FAILED\n" << log << std::endl;
		return success;
	}
	// free resources
	// not sure we do this here?
	for (auto& shader : shaders)
	{
		glDeleteShader(shader);
	}
	return shaderProgram;
}