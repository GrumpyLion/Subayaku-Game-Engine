#pragma once

#include "Cache\SMeshDesc.h"

namespace Graphics
{
	class Primitives
	{
	public:
		static void GetQuad(SMeshDesc &a_Desc)
		{
			Vector3f tempVec3;
			Vector2f tempVec2;

			tempVec3.Set(0.5f, 0.5f, 0.0f);
			a_Desc.Vertices.push_back(tempVec3);

			tempVec3.Set(0.5f, -0.5f, 0.0f);
			a_Desc.Vertices.push_back(tempVec3);

			tempVec3.Set(-0.5f, -0.5f, 0.0f);
			a_Desc.Vertices.push_back(tempVec3);

			tempVec3.Set(-0.5f, 0.5f, 0.0f);
			a_Desc.Vertices.push_back(tempVec3);
			
			tempVec2.Set(1.0f, 1.0f);
			a_Desc.TexCoords.push_back(tempVec2);

			tempVec2.Set(1.0f, 0.0f);
			a_Desc.TexCoords.push_back(tempVec2);

			tempVec2.Set(0.0f, 0.0f);
			a_Desc.TexCoords.push_back(tempVec2);

			tempVec2.Set(0.0f, 1.0f);
			a_Desc.TexCoords.push_back(tempVec2);

			a_Desc.Indices.push_back(0);
			a_Desc.Indices.push_back(1);
			a_Desc.Indices.push_back(3);

			a_Desc.Indices.push_back(1);
			a_Desc.Indices.push_back(2);
			a_Desc.Indices.push_back(3);
		}


		//Returns a triangle mesh with indices
		static void GetPlaneTri(SMeshDesc &a_Desc, float a_XD, float a_Y, float a_ZD)
		{
			int index = 0;
			for (int x = -(int)a_XD / 2; x < (int)a_XD / 2; x++)
			{
				for (int z = -(int)a_ZD / 2; z < (int)a_ZD / 2; z++)
				{
					Vector3f tempPos1, tempPos2, tempPos3, tempPos4;
					Vector2f tempUV;

					tempPos1.Set((float)x, a_Y, (float)z);
					a_Desc.Vertices.push_back(tempPos1);

					tempPos2.Set((float)x, a_Y, (float)z + 1.0f);
					a_Desc.Vertices.push_back(tempPos2);

					tempPos3.Set((float)x + 1.0f, a_Y, (float)z + 1.0f);
					a_Desc.Vertices.push_back(tempPos3);

					tempPos4.Set((float)x + 1.0f, a_Y, (float)z);
					a_Desc.Vertices.push_back(tempPos4);

					tempUV.Set(((float)x + a_XD / 2) / a_XD, ((float)z + a_ZD / 2) / a_ZD);
					a_Desc.TexCoords.push_back(tempUV);

					tempUV.Set(((float)x + a_XD / 2) / a_XD, ((float)z + a_ZD / 2 + 1) / a_ZD);
					a_Desc.TexCoords.push_back(tempUV);

					tempUV.Set(((float)x + a_XD / 2 + 1) / a_XD, ((float)z + a_ZD / 2 + 1) / a_ZD);
					a_Desc.TexCoords.push_back(tempUV);

					tempUV.Set(((float)x + a_XD / 2 + 1) / a_XD, ((float)z + a_ZD / 2) / a_ZD);
					a_Desc.TexCoords.push_back(tempUV);

					a_Desc.Indices.push_back(index);
					a_Desc.Indices.push_back(index + 1);
					a_Desc.Indices.push_back(index + 2);

					a_Desc.Indices.push_back(index + 2);
					a_Desc.Indices.push_back(index + 3);
					a_Desc.Indices.push_back(index + 0);

					index += 4;

					Vector3f first = (tempPos2 - tempPos3);
					Vector3f second = (tempPos4 - tempPos1);

					Vector3f n1 = Vector3f::Cross(first, second);
					n1.Normalize();
					//n1.Invert();

					a_Desc.Normals.push_back(n1);
					a_Desc.Normals.push_back(n1);
					a_Desc.Normals.push_back(n1);
					a_Desc.Normals.push_back(n1);
				}
			}
		}
		//Returns a triangle mesh with indices
		static void GetPlane(SMeshDesc &a_Desc, float a_XD, float a_Y, float a_ZD)
		{
			int index = 0;
			for (int x = -(int)a_XD / 2; x < (int)a_XD / 2; x++)
			{
				for (int z = -(int)a_ZD / 2; z < (int)a_ZD / 2; z++)
				{
					Vector3f tempPos1, tempPos2, tempPos3, tempPos4;
					Vector2f tempUV;

					tempPos1.Set((float)x, a_Y, (float)z);
					a_Desc.Vertices.push_back(tempPos1);

					tempPos2.Set((float)x, a_Y, (float)z + 1.0f);
					a_Desc.Vertices.push_back(tempPos2);

					tempPos3.Set((float)x + 1.0f, a_Y, (float)z + 1.0f);
					a_Desc.Vertices.push_back(tempPos3);

					tempPos4.Set((float)x + 1.0f, a_Y, (float)z);
					a_Desc.Vertices.push_back(tempPos4);

					tempUV.Set(((float)x + a_XD/2) / a_XD, ((float)z + a_ZD/2) / a_ZD);
					a_Desc.TexCoords.push_back(tempUV);

					tempUV.Set(((float)x + a_XD/2) / a_XD, ((float)z + a_ZD/2 + 1) / a_ZD);
					a_Desc.TexCoords.push_back(tempUV);

					tempUV.Set(((float)x + a_XD/2 + 1) / a_XD, ((float)z + a_ZD/2 + 1) / a_ZD);
					a_Desc.TexCoords.push_back(tempUV);

					tempUV.Set(((float)x + a_XD/2 + 1) / a_XD, ((float)z + a_ZD/2) / a_ZD);
					a_Desc.TexCoords.push_back(tempUV);

					a_Desc.Indices.push_back(index);
					a_Desc.Indices.push_back(index + 1);
					a_Desc.Indices.push_back(index + 3);

					a_Desc.Indices.push_back(index + 1);
					a_Desc.Indices.push_back(index + 2);
					a_Desc.Indices.push_back(index + 3);

					index += 4;

					Vector3f first = (tempPos2 - tempPos3);
					Vector3f second = (tempPos4 - tempPos1);

					Vector3f n1 = Vector3f::Cross(first, second);
					n1.Normalize();
					//n1.Invert();

					a_Desc.Normals.push_back(n1);
					a_Desc.Normals.push_back(n1);
					a_Desc.Normals.push_back(n1);
					a_Desc.Normals.push_back(n1);
				}
			}
		}

		static void GetSphere(SMeshDesc &a_Desc, float a_Radius, float a_Space)
		{
			const int VertexCount = (int)((90 / a_Space) * (360 / a_Space) * 4);
			a_Desc.Vertices.reserve(VertexCount);

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

					a_Desc.Vertices.push_back(tempPos1);
					a_Desc.TexCoords.push_back(tempUV);

					tempPos2.x = a_Radius * std::sin(j / 180 * PI) * std::sin((i + a_Space) / 180 * PI);
					tempPos2.y = a_Radius * std::cos(j / 180 * PI) * std::sin((i + a_Space) / 180 * PI);
					tempPos2.z = a_Radius * std::cos((i + a_Space) / 180 * PI);

					tempUV.x = (2 * (i + a_Space)) / 360;
					tempUV.y = (j) / 360;

					a_Desc.Vertices.push_back(tempPos2);
					a_Desc.TexCoords.push_back(tempUV);

					tempPos3.x = a_Radius * std::sin((j + a_Space) / 180 * PI) * std::sin(i / 180 * PI);
					tempPos3.y = a_Radius * std::cos((j + a_Space) / 180 * PI) * std::sin(i / 180 * PI);
					tempPos3.z = a_Radius * std::cos(i / 180 * PI);

					tempUV.x = (2 * (i)) / 360;
					tempUV.y = (j + a_Space) / 360;

					a_Desc.Vertices.push_back(tempPos3);
					a_Desc.TexCoords.push_back(tempUV);

					tempPos4.x = a_Radius * std::sin((j + a_Space) / 180 * PI) * std::sin((i + a_Space) / 180 * PI);
					tempPos4.y = a_Radius * std::cos((j + a_Space) / 180 * PI) * std::sin((i + a_Space) / 180 * PI);
					tempPos4.z = a_Radius * std::cos((i + a_Space) / 180 * PI);

					tempUV.x = (2 * (i + a_Space)) / 360;
					tempUV.y = (j + a_Space) / 360;

					a_Desc.Vertices.push_back(tempPos4);
					a_Desc.TexCoords.push_back(tempUV);

					a_Desc.Indices.push_back(index + 3);
					a_Desc.Indices.push_back(index + 1);
					a_Desc.Indices.push_back(index);

					a_Desc.Indices.push_back(index);
					a_Desc.Indices.push_back(index + 2);
					a_Desc.Indices.push_back(index + 3);
					 
					index += 4;

					Vector3f first = (tempPos2 - tempPos3);
					Vector3f second = (tempPos4 - tempPos1);
					
					Vector3f n1 = Vector3f::Cross(first, second);
					n1.Normalize();
					n1.Invert();

					a_Desc.Normals.push_back(n1);
					a_Desc.Normals.push_back(n1);
					a_Desc.Normals.push_back(n1);
					a_Desc.Normals.push_back(n1);
				}
			}
		}
	};
}