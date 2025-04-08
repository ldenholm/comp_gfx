#pragma once
#include "glad/glad.h"

class Transformations {
public:
	// todo: parameterize these
	static void rotate(GLuint &shaderProgram);
	static void translate(GLuint& shaderProgram);
};