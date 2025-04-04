#version 330 core
uniform vec4 dynamicColor;
out vec4 FragColor;
void main()
{
	FragColor = dynamicColor;
};