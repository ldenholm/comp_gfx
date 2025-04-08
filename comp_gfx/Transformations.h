#pragma once
#include "glad/glad.h"

class Transformations {
public:
	// todo: parameterize these
	static void rotate(GLuint &shaderProgram);
	static void translate(GLuint& shaderProgram);
	static void scale(GLuint& shaderProgram, float_t lower, float_t upper);
	static void s_r_t(GLuint& shaderProgram);
};