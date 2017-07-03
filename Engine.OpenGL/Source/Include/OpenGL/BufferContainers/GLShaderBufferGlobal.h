#pragma once

#include "OpenGL\GLShaderBuffer.h"

#include <memory>

namespace Graphics
{
	namespace OpenGL
	{
		class GLRenderer;

		class GLShaderBufferGlobal
		{
		private:
			GLRenderer *m_Renderer = nullptr;

			std::unique_ptr<GLShaderBuffer> m_DynamicGlobalBuffer = nullptr;
			std::unique_ptr<GLShaderBuffer> m_ConstantGlobalBuffer = nullptr;

			//OpenGL has another way of sorting data (std140)
			//In the std140 Format everything is either 2 elements big or 4
			//That means a float will be at the end a vec2
			//A vec3 will be vec4 and so on

#pragma pack(push, 1)
			struct DynamicBuffer
			{
				Matrix4f Projection;
				Matrix4f View;

				Vector4f CameraPos;
				Vector2f Time;
				
				Vector2f Padding01;

				//Directional Light -- 
				Vector4f LightDirection;
				Vector4f LightColor;
			};
#pragma pack(pop)

		public:
			GLShaderBufferGlobal(GLRenderer *a_Renderer);
			void Bind();
		};
	}
}