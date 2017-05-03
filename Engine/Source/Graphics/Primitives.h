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

		static Mesh *GetPlane(float a_XD, float a_Y, float a_ZD)
		{
			Mesh *temp = new Mesh();

			int index = 0;
			for (int x = -(int)a_XD / 2; x < (int)a_XD / 2; x++)
			{
				for (int z = -(int)a_ZD / 2; z < (int)a_ZD / 2; z++)
				{
					Vector3f tempPos1, tempPos2, tempPos3, tempPos4;
					Vector2f tempUV;

					tempPos1.Set(x, a_Y, z);
					temp->Vertices.push_back(tempPos1);

					tempPos2.Set(x, a_Y, z + 1.0f);
					temp->Vertices.push_back(tempPos2);

					tempPos3.Set(x + 1.0f, a_Y, z + 1.0f);
					temp->Vertices.push_back(tempPos3);

					tempPos4.Set(x + 1.0f, a_Y, z);
					temp->Vertices.push_back(tempPos4);

					tempUV.Set((x + a_XD/2) / a_XD, (z + a_ZD/2) / a_ZD);
					temp->TexCoords.push_back(tempUV);

					tempUV.Set((x + a_XD/2) / a_XD, (z + a_ZD/2 + 1) / a_ZD);
					temp->TexCoords.push_back(tempUV);

					tempUV.Set((x + a_XD/2 + 1) / a_XD, (z + a_ZD/2 + 1) / a_ZD);
					temp->TexCoords.push_back(tempUV);

					tempUV.Set((x + a_XD/2 + 1) / a_XD, (z + a_ZD/2) / a_ZD);
					temp->TexCoords.push_back(tempUV);

					temp->Indices.push_back(index);
					temp->Indices.push_back(index + 1);
					temp->Indices.push_back(index + 3);

					temp->Indices.push_back(index + 1);
					temp->Indices.push_back(index + 2);
					temp->Indices.push_back(index + 3);

					index += 4;

					Vector3f first = (tempPos2 - tempPos3);
					Vector3f second = (tempPos4 - tempPos1);

					Vector3f n1 = Vector3f::Cross(first, second);
					n1.Normalize();
					//n1.Invert();

					temp->Normals.push_back(n1);
					temp->Normals.push_back(n1);
					temp->Normals.push_back(n1);
					temp->Normals.push_back(n1);
				}
			}
			return temp;
		}

		static Mesh *GetSphere(float a_Radius, float a_Space)
		{
			Mesh* temp = new Mesh();
			const int VertexCount = (int)((90 / a_Space) * (360 / a_Space) * 4);
			temp->Vertices.reserve(VertexCount);

			int index = 0;
			for (float i = 0; i <= 180 - a_Space; i += a_Space)
			{
				for (float j = 0; j <= 360 - a_Space; j += a_Space)
				{
					Vector3f tempPos1, tempPos2, tempPos3, tempPos4;
					Vector2f tempUV;

					tempPos1.x = a_Radius * std::sin(j / 180 * PI) * std::sin(i / 180 * PI);
					tempPos1.y = a_Radius * std::cos(j / 180 * PI) * std::sin(i / 180 * PI);
					tempPos1.z = a_Radius * std::cos(i / 180 * PI);
					
					tempUV.x = (2 * i) / 360;
					tempUV.y = (j) / 360;

					temp->Vertices.push_back(tempPos1);
					temp->TexCoords.push_back(tempUV);

					tempPos2.x = a_Radius * std::sin(j / 180 * PI) * std::sin((i + a_Space) / 180 * PI);
					tempPos2.y = a_Radius * std::cos(j / 180 * PI) * std::sin((i + a_Space) / 180 * PI);
					tempPos2.z = a_Radius * std::cos((i + a_Space) / 180 * PI);

					tempUV.x = (2 * (i + a_Space)) / 360;
					tempUV.y = (j) / 360;

					temp->Vertices.push_back(tempPos2);
					temp->TexCoords.push_back(tempUV);

					tempPos3.x = a_Radius * std::sin((j + a_Space) / 180 * PI) * std::sin(i / 180 * PI);
					tempPos3.y = a_Radius * std::cos((j + a_Space) / 180 * PI) * std::sin(i / 180 * PI);
					tempPos3.z = a_Radius * std::cos(i / 180 * PI);

					tempUV.x = (2 * (i)) / 360;
					tempUV.y = (j + a_Space) / 360;

					temp->Vertices.push_back(tempPos3);
					temp->TexCoords.push_back(tempUV);

					tempPos4.x = a_Radius * std::sin((j + a_Space) / 180 * PI) * std::sin((i + a_Space) / 180 * PI);
					tempPos4.y = a_Radius * std::cos((j + a_Space) / 180 * PI) * std::sin((i + a_Space) / 180 * PI);
					tempPos4.z = a_Radius * std::cos((i + a_Space) / 180 * PI);

					tempUV.x = (2 * (i + a_Space)) / 360;
					tempUV.y = (j + a_Space) / 360;

					temp->Vertices.push_back(tempPos4);
					temp->TexCoords.push_back(tempUV);

					temp->Indices.push_back(index + 3);
					temp->Indices.push_back(index + 1);
					temp->Indices.push_back(index);

					temp->Indices.push_back(index);
					temp->Indices.push_back(index + 2);
					temp->Indices.push_back(index + 3);
					 
					index += 4;

					Vector3f first = (tempPos2 - tempPos3);
					Vector3f second = (tempPos4 - tempPos1);
					
					Vector3f n1 = Vector3f::Cross(first, second);
					n1.Normalize();
					n1.Invert();

					temp->Normals.push_back(n1);
					temp->Normals.push_back(n1);
					temp->Normals.push_back(n1);
					temp->Normals.push_back(n1);
				}
			}

			return temp;
		}
	};
}