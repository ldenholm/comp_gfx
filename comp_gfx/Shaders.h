#pragma once
#include <glad/glad.h>
#include <vector>

class Shaders {
	public:
		static GLuint compile_and_create_shader(GLenum shaderType, const char* shaderSrcPath, GLuint& shader);
		static GLuint create_and_link_shader_program(std::vector<GLuint>& shaders);
};