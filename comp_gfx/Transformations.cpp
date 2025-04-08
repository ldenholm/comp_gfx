#include "glad/glad.h"
#include "glm/glm.hpp"
#include "Transformations.h"

void Transformations::rotate(GLuint& shaderProgram)
{
	static float angleRadians = 0.0f;
	static float beta = 0.01f;
	angleRadians += beta;
	if ((angleRadians >= 3.14f) || (angleRadians <= -3.14f))
	{
		beta *= -1.0f;
	}
	glm::mat4 rotationMatrix = glm::mat4(1.0f);
	// this rotation matrix is anchored to the x axis
	// let R be a rotation matrix, R in R^(4x4) since we account for z axis and w column
	/*
	*	note a = current angle, b is desired angle, (x1, y1) = current coords, (x2, y2) = desired coords.

		use angle sum identity:
		sin(a + b) = sin(a)cos(b) + cos(a)sin(b)
		cos(a + b) = cos(a)cos(b) - sin(a)sin(b)

		for unit circle note:
		sin(a) = opp/hyp = opp/1 = opp = y1
		cos(a) = adj/hyp = adj/1 = adj = x1

		cos(a + b) = x2
		sin(a + b) = y2

		putting it all together:
		x2 = y1*cos(b) + x1*sin(b)
		y2 = x1*cos(b) - y1*sin(b)

		reorder:
		x1*cos(b) - y1*sin(b)
		x1*sin(b) + y1*cos(b)

		recognize Ax = b structure where R is rotation matrix acting on b our current position
		[cos(b) -sin(b) 0 0]	 [x]
		|sin(b)  cos(b) 0 0|  x  |y|
		|0          0   1 0|	 |z|
		[0          0   0 1]	 [w]

	*/
	rotationMatrix[0][0] = cosf(angleRadians);
	rotationMatrix[0][1] = -sinf(angleRadians);
	rotationMatrix[1][0] = sinf(angleRadians);
	rotationMatrix[1][1] = cosf(angleRadians);
	GLint gTranslationLocation = glGetUniformLocation(shaderProgram, "gTranslation");
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(gTranslationLocation, 1, GL_FALSE, &rotationMatrix[0][0]);
}

void Transformations::translate(GLuint& shaderProgram)
{
	static float scale = 0.0f;
	static float delta = 0.005f;
	scale += delta;
	if ((scale >= 0.3f) || (scale <= -0.6f))
	{
		delta *= -1.0f;
	}
	glm::mat4 translationMatrix = glm::mat4(1.0f);
	translationMatrix[0][3] = scale * 2; // x axis translation
	translationMatrix[1][3] = scale; // y axis translation
	GLint gTranslationLocation = glGetUniformLocation(shaderProgram, "gTranslation");
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(gTranslationLocation, 1, GL_FALSE, &translationMatrix[0][0]);
}

void Transformations::scale(GLuint& shaderProgram, float_t lower, float_t upper)
{
	static float scale = 0.0f;
	static float delta = 0.01f;
	scale += delta;
	if ((scale <= lower) || (scale >= upper))
	{
		delta *= -1.0f;
	}

	glm::mat4 scaleMatrix = glm::mat4(1.0f);
	GLint gTranslationLocation = glGetUniformLocation(shaderProgram, "gTranslation");
	scaleMatrix[0][0] = scale;
	scaleMatrix[1][1] = scale; // only need to scale x and y axes.
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(gTranslationLocation, 1, GL_FALSE, &scaleMatrix[0][0]);
}

