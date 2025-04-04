#include "Shaders.h"
#include <fstream>
#include <string>
#include <iostream>

//template<typename T>
GLuint Shaders::Shaders::compile_and_build_shader(const char* shaderSrcPath)
{
	std::cout << "provided path: " << shaderSrcPath << std::endl;
	std::ifstream infile{ shaderSrcPath };
	if (infile)
	{
		std::string line;
		while (std::getline(infile, line))
		{
			std::cout << line << std::endl;
		}
	}
	return GLuint();
}