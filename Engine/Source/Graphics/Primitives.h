#pragma once

#include "Mesh.h"

namespace Graphics
{
	class Primitives
	{
	public:
		static Mesh *GetBox()
		{
			Mesh *temp = new Mesh();

			temp->Vertices.push_back(-1);
			temp->Vertices.push_back(-1);
			temp->Vertices.push_back(-1);

			temp->Normals.push_back(-1);
			temp->Normals.push_back(-1);
			temp->Normals.push_back(-1);

			temp->Vertices.push_back(1);
			temp->Vertices.push_back(-1);
			temp->Vertices.push_back(-1);

			temp->Normals.push_back(1);
			temp->Normals.push_back(-1);
			temp->Normals.push_back(-1);

			temp->Vertices.push_back(1);
			temp->Vertices.push_back(1);
			temp->Vertices.push_back(-1);

			temp->Normals.push_back(1);
			temp->Normals.push_back(1);
			temp->Normals.push_back(-1);

			temp->Vertices.push_back(-1);
			temp->Vertices.push_back(1);
			temp->Vertices.push_back(-1);

			temp->Normals.push_back(-1);
			temp->Normals.push_back(1);
			temp->Normals.push_back(-1);

			temp->Vertices.push_back(-1);
			temp->Vertices.push_back(-1);
			temp->Vertices.push_back(1);

			temp->Normals.push_back(-1);
			temp->Normals.push_back(-1);
			temp->Normals.push_back(1);

			temp->Vertices.push_back(1);
			temp->Vertices.push_back(-1);
			temp->Vertices.push_back(1);
			
			temp->Normals.push_back(1);
			temp->Normals.push_back(-1);
			temp->Normals.push_back(0);

			temp->Vertices.push_back(1);
			temp->Vertices.push_back(1);
			temp->Vertices.push_back(1);

			temp->Normals.push_back(0);
			temp->Normals.push_back(0);
			temp->Normals.push_back(0);

			temp->Vertices.push_back(-1);
			temp->Vertices.push_back(1);
			temp->Vertices.push_back(1);

			temp->Normals.push_back(-0);
			temp->Normals.push_back(0);
			temp->Normals.push_back(0);

			//Front
			temp->Indices.push_back(0);
			temp->Indices.push_back(1);
			temp->Indices.push_back(2);

			temp->Indices.push_back(0);
			temp->Indices.push_back(2);
			temp->Indices.push_back(3);

			//Left
			temp->Indices.push_back(0);
			temp->Indices.push_back(4);
			temp->Indices.push_back(3);

			temp->Indices.push_back(4);
			temp->Indices.push_back(7);
			temp->Indices.push_back(3);

			//Back
			temp->Indices.push_back(4);
			temp->Indices.push_back(5);
			temp->Indices.push_back(6);

			temp->Indices.push_back(4);
			temp->Indices.push_back(7);
			temp->Indices.push_back(6);

			//Right
			temp->Indices.push_back(1);
			temp->Indices.push_back(5);
			temp->Indices.push_back(2);

			temp->Indices.push_back(5);
			temp->Indices.push_back(2);
			temp->Indices.push_back(6);

			//Top
			temp->Indices.push_back(3);
			temp->Indices.push_back(2);
			temp->Indices.push_back(6);

			temp->Indices.push_back(3);
			temp->Indices.push_back(7);
			temp->Indices.push_back(6);

			//Bottom
			temp->Indices.push_back(0);
			temp->Indices.push_back(1);
			temp->Indices.push_back(5);

			temp->Indices.push_back(0);
			temp->Indices.push_back(4);
			temp->Indices.push_back(5);

			return temp;
		}
	};
}