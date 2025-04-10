#include "Mesh.h"

Mesh::Mesh(const aiScene* scene)
{
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	
	// store model data in vbo + ibo
	numVertices = scene->mMeshes[0]->mNumVertices;
	numIndices = scene->mMeshes[0]->mNumFaces * 3;
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(
		GL_ARRAY_BUFFER, 
		numVertices * sizeof(aiVector3D), 
		scene->mMeshes[0]->mVertices, 
		GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	unsigned int* indices = new unsigned int[numIndices];
	
	for (int i = 0; i < numIndices; i+=3)
	{
		indices[i] = scene->mMeshes[0]->mFaces[i / 3].mIndices[0];
		indices[i + 1] = scene->mMeshes[0]->mFaces[i / 3].mIndices[1];
		indices[i + 2] = scene->mMeshes[0]->mFaces[i / 3].mIndices[2];
	}

	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	delete[] indices;
};