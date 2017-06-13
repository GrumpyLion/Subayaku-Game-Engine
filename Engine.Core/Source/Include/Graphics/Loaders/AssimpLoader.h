#pragma once

#include <Assimp/Importer.hpp>   
#include <Assimp/scene.h>         
#include <Assimp/postprocess.h>

#include "Graphics\Descriptions\SMeshDesc.h"

#include "Utilities\FileSystem.h"

inline bool LoadAssimpObj(Graphics::SMeshDesc &a_Desc)
{
	Assimp::Importer importer;

	auto temp = Core::FileSystem::StaticClass()->GetFile(a_Desc.FilePath);

	if (temp == nullptr)
		return false;

	const aiScene* scene = importer.ReadFileFromMemory(&temp->Data[0], temp->FileSize, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals  | aiProcess_CalcTangentSpace);
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

		aiVector3D nor = mesh->mNormals[i];
		a_Desc.Normals.push_back(Vector3f(nor.x, nor.y, nor.z));

		if (mesh->mTangents != nullptr)
		{
			aiVector3D tan = mesh->mTangents[i];
			a_Desc.Tangents.push_back(Vector3f(tan.x, tan.y, tan.z));
		}

		if (mesh->mBitangents != nullptr)
		{
			aiVector3D bi = mesh->mTangents[i];
			a_Desc.Bitangents.push_back(Vector3f(bi.x, bi.y, bi.z));
		}

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
