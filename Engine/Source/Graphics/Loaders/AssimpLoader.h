#pragma once

#include <Assimp/Importer.hpp>   
#include <Assimp/scene.h>         
#include <Assimp/postprocess.h>

#include "Graphics\Cache\SMeshDesc.h"

inline bool LoadAssimpObj(Graphics::SMeshDesc &a_Desc)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(a_Desc.FilePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_CalcTangentSpace);
	if (!scene) {
		fprintf(stderr, importer.GetErrorString());
		getchar();
		return false;
	}
	const aiMesh* mesh = scene->mMeshes[0]; // In this simple example code we always use the 1rst mesh (in OBJ files there is often only one anyway)

	a_Desc.Vertices.reserve(mesh->mNumVertices);
	a_Desc.Normals.reserve(mesh->mNumVertices);
	a_Desc.Indices.reserve(3 * mesh->mNumFaces);

	if (mesh->mTextureCoords[0])
		a_Desc.TexCoords.reserve(mesh->mNumVertices);

	for (unsigned int i = 0; i<mesh->mNumVertices; i++)
	{
		aiVector3D pos = mesh->mVertices[i];
		a_Desc.Vertices.push_back(Vector3f(pos.x, pos.y, pos.z));

		Vector3f nor;
		nor.x = mesh->mNormals[i].x;
		nor.y = mesh->mNormals[i].y;
		nor.z = mesh->mNormals[i].z;
		a_Desc.Normals.push_back(nor);

		Vector3f tan;
		tan.x = mesh->mTangents[i].x;
		tan.y = mesh->mTangents[i].y;
		tan.z = mesh->mTangents[i].z;
		a_Desc.Tangents.push_back(tan);

		Vector3f bi;
		bi.x = mesh->mBitangents[i].x;
		bi.y = mesh->mBitangents[i].y;
		bi.z = mesh->mBitangents[i].z;
		a_Desc.Bitangents.push_back(bi);

		if (mesh->mTextureCoords[0])
		{
			Vector2f uv;
			uv.x = mesh->mTextureCoords[0][i].x;
			uv.y = mesh->mTextureCoords[0][i].y;
			a_Desc.TexCoords.push_back(uv);
		}
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			a_Desc.Indices.push_back(face.mIndices[j]);
		}
	}
	return true;
}
