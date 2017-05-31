#pragma once

#include "Graphics\Base\BaseRenderer.h"
#include <GLEW\Include\glew.h>
#include <gl/gl.h>

#include "GLShaderBufferContainer.h"
#include "GLEntity.h"
#include "GLTexture.h"
#include "GLShader.h"
#include "GLShaderBuffer.h"
#include "GLMesh.h"

#include <unordered_map>
#include <memory>

namespace Graphics
{
	namespace OpenGL
	{
		class GLEntity;

		class GLRenderer : public BaseRenderer<GLEntity, GLTexture, GLMesh, GLShader, GLShaderBuffer>
		{
		private:
			HDC m_HDC{};
			SRendererDesc m_Desc{};
			HGLRC m_Context{};

			std::unique_ptr<GLShaderBufferContainer> m_Container;
		public:

			__declspec(dllexport) ~GLRenderer();

			__declspec(dllexport) bool Initialize(SRendererDesc &a_Desc) override;
			__declspec(dllexport) void Render() override;

		};
	}
}