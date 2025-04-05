#version 330 core
layout (location = 0) in vec3 Position;

uniform mat4 gTranslation

void main()
{
	gl_Position = gTranslation * vec4(Position, 1.0);
};

#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 gTranslation

out vec4 vertexColor;

void main()
{
	gl_Position = gTranslation * vec4(aPos, 1.0);
	vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
};