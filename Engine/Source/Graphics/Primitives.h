#pragma once

#include "Mesh.h"

namespace Graphics
{
	class Primitives
	{
	public:
		static Mesh *GetQuad()
		{
			Mesh *temp = new Mesh();
			Vector3f tempVec3;
			Vector2f tempVec2;

			tempVec3.Set(0.5f, 0.5f, 0.0f);
			temp->Vertices.push_back(tempVec3);

			tempVec3.Set(0.5f, -0.5f, 0.0f);
			temp->Vertices.push_back(tempVec3);

			tempVec3.Set(-0.5f, -0.5f, 0.0f);
			temp->Vertices.push_back(tempVec3);

			tempVec3.Set(-0.5f, 0.5f, 0.0f);
			temp->Vertices.push_back(tempVec3);
			
			tempVec2.Set(1.0f, 1.0f);
			temp->TexCoords.push_back(tempVec2);

			tempVec2.Set(1.0f, 0.0f);
			temp->TexCoords.push_back(tempVec2);

			tempVec2.Set(0.0f, 0.0f);
			temp->TexCoords.push_back(tempVec2);

			tempVec2.Set(0.0f, 1.0f);
			temp->TexCoords.push_back(tempVec2);

			temp->Indices.push_back(0);
			temp->Indices.push_back(1);
			temp->Indices.push_back(3);

			temp->Indices.push_back(1);
			temp->Indices.push_back(2);
			temp->Indices.push_back(3);

			return temp;
		}
	};
}