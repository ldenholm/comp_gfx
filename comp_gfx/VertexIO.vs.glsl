#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 gTranslation;
out vec4 vertexColor;
void main()
{
	gl_Position = vec4(aPos, 1.0) * gTranslation;
	vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
};