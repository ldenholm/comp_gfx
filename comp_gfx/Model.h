#pragma once
#include "vector"
#include "string"
#include "Mesh.h"

using namespace std;
class Model
{
public:
	Model(string path);
	void Draw();
private:
	vector<Mesh> meshes;
	string directory;

	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		string typeName);
};