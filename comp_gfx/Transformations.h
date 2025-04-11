#pragma once
#include "glad/glad.h"

class Transformations {
public:
	// todo: parameterize these
	static void rotate_x(GLuint &shaderProgram);
	static void translate(GLuint& shaderProgram);
	static void scale(GLuint& shaderProgram, float_t lower, float_t upper);
	static void scaleByX(GLuint& shaderProgram, float_t X);
	static void s_r_t(GLuint& shaderProgram);
	static void identity(GLuint& shaderProgram);
	static void rotate_y(GLuint& shaderProgram);
	static void projection(GLuint& shaderProgram);
};