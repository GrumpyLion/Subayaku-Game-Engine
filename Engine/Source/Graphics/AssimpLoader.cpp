#include "AssimpLoader.h"

#include <Assimp/Importer.hpp>   
#include <Assimp/scene.h>         
#include <Assimp/postprocess.h>

bool loadAssimp(
	const char * path,
	std::vector<unsigned int> & indices,
	std::vector<Vector3f> & vertices,
	std::vector<Vector2f> & uvs,
	std::vector<Vector3f> & normals
) {

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
	if (!scene) {
		fprintf(stderr, importer.GetErrorString());
		getchar();
		return false;
	}
	const aiMesh* mesh = scene->mMeshes[0]; // In this simple example code we always use the 1rst mesh (in OBJ files there is often only one anyway)

	vertices.reserve(mesh->mNumVertices);
	normals.reserve(mesh->mNumVertices);	
	indices.reserve(3 * mesh->mNumFaces);
	if (mesh->mTextureCoords[0])
		uvs.reserve(mesh->mNumVertices);

	for (unsigned int i = 0; i<mesh->mNumVertices; i++) 
	{
		aiVector3D pos = mesh->mVertices[i];
		vertices.push_back(Vector3f(pos.x, pos.y, pos.z));

		Vector3f nor;
		nor.x = mesh->mNormals[i].x;
		nor.y = mesh->mNormals[i].y;
		nor.z = mesh->mNormals[i].z;
		normals.push_back(nor);

		if (mesh->mTextureCoords[0])
		{
			Vector2f uv;
			uv.x = mesh->mTextureCoords[0][i].x;
			uv.y = mesh->mTextureCoords[0][i].y;
			uvs.push_back(uv);
		}
	}	

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
}
