#pragma once

#include <glad/glad.h>
#include <assimp/scene.h>

class Mesh {
public:
	GLuint vbo, ibo;
	int numVertices, numIndices;

	Mesh(const aiScene* scene);
	~Mesh();
};