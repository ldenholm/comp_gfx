#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Transformations.h"
#include <numbers>

void Transformations::rotate_x(GLuint& shaderProgram)
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

void Transformations::s_r_t(GLuint& shaderProgram)
{
	// Note we apply transformation left to right: RotateTranslateScale
	// note this is only a translate and rotate:
	// translate
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
	

	// rotate

	static float angleRadians = 0.0f;
	static float beta = 0.01f;
	angleRadians += beta;
	if ((angleRadians >= 3.14f) || (angleRadians <= -3.14f))
	{
		beta *= -1.0f;
	}
	glm::mat4 rotationMatrix = glm::mat4(1.0f);
	
	rotationMatrix[0][0] = cosf(angleRadians);
	rotationMatrix[0][1] = -sinf(angleRadians);
	rotationMatrix[1][0] = sinf(angleRadians);
	rotationMatrix[1][1] = cosf(angleRadians);

	// resultant matrix
	glm::mat4 linearTransform = rotationMatrix * translationMatrix;
	
	GLint gTranslationLocation = glGetUniformLocation(shaderProgram, "gTranslation");
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(gTranslationLocation, 1, GL_FALSE, &linearTransform[0][0]);

}

void Transformations::identity(GLuint& shaderProgram)
{
	glm::mat4 identityMatrix = glm::mat4(1.0f);
	GLint gTranslationLocation = glGetUniformLocation(shaderProgram, "gTranslation");
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(gTranslationLocation, 1, GL_FALSE, &identityMatrix[0][0]);
}

void Transformations::rotate_y(GLuint& shaderProgram)
{
	static float scale = 0.0f;
	scale += 0.01;
	glm::mat4 R = glm::mat4(1.0f);
	R[0][0] = cosf(scale);
	R[0][2] = -sinf(scale);
	R[2][0] = sinf(scale);
	R[2][2] = cosf(scale);
	GLint gTranslationLocation = glGetUniformLocation(shaderProgram, "gTranslation");
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(gTranslationLocation, 1, GL_FALSE, &R[0][0]);
}

void Transformations::projection(GLuint& shaderProgram)
{

	static float scale = 0.0f;
	scale += 0.01;
	glm::mat4 rotation = glm::mat4(1.0f);
	rotation[0][0] = cosf(scale);
	rotation[0][2] = -sinf(scale);
	rotation[2][0] = sinf(scale);
	rotation[2][2] = cosf(scale);

	/* The big idea here is that we are projecting a vector in from the world onto a viewport
	   to create 3d perspective. We are projecting a vector in R^3 onto R^2.

	   Note we fix camera to origin (0,0,0).

	   See perspective.png to get the idea. We are interested in finding P' which represents
	   P's location in the viewport.
	   Note: P_x = x, P_y = y, P_z = z.
			 alpha = field of view (FOV) in deg.
	   P'_z = d, the distance along z-axis to the viewport plane.
	   P'_y is given in terms of P: (P_y * d) / P_z = y / z * tan(alpha/2).
	   P'_x is given in terms of P: (P_x * d) / P_z = x / z * tan(alpha/2).
	*/

	// here we create an identity mat4 and multiply it by a vec3 specifying -2 for the z coords.
	// note that even though mat4 is multipling a vec3 the vec3 is treated as a vec4 inserting 1.0f
	// into the 4th row.
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f));
	
	//float alphaRads = 90.0f * (std::numbers::pi / 180);
	//float tanHalfAlpha = tanf(alphaRads / 2.0f);
	//float d = 1/tanHalfAlpha;

	//glm::mat4 projection = glm::mat4(1.0f);
	//projection[0][0] = d;
	//projection[1][1] = d;
	//projection[3][2] = 1.0f;
	//projection[3][3] = 0.0f;

	//glm::mat4 transform_first = glm::matrixCompMult(rotation, translation);
	//glm::mat4 transform_final = glm::matrixCompMult(transform_first, projection);

	//glm::mat4 transform = projection * rotation * translation;
	// note higher value of 'near' = box further away
	// consider we are at (0, 0, 0) so we must move the object down the z-axis in the negative direction.
	// therefore z must be in (-100, -0.1) to avoid clipping
	glm::mat4 projection = glm::perspective(glm::radians(90.0f), (4.0f / 3.0f), 0.1f, 50.0f);

	//glm::mat4 transform = projection * rotation * translation;
	
	glm::mat4 transform = projection * translation * rotation;
	
	GLint gTranslationLocation = glGetUniformLocation(shaderProgram, "gTranslation");
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(gTranslationLocation, 1, GL_FALSE, &transform[0][0]);
}
