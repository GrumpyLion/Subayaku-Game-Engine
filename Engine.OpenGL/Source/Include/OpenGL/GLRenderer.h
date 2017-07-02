#pragma once

#include "Graphics\Bases\BaseRenderer.h"
#include <GLEW\Include\glew.h>
#include <GLEW\Include\wglew.h>
#include <gl/gl.h>

#include "GLShaderBufferContainer.h"
#include "RenderPasses\GLRenderPassGBuffer.h"

#include <unordered_map>
#include <memory>

namespace Graphics
{
	namespace OpenGL
	{
		class GLEntity;

		class GLRenderer : public BaseRenderer
		{
		private:
			HDC m_HDC{};
			HGLRC m_Context{};

			std::unique_ptr<GLRenderPassGBuffer> m_RenderPass;

			void Resize() final;
		public:

			__declspec(dllexport) ~GLRenderer();
			__declspec(dllexport) GLRenderer(Core::Engine *a_Engine);

			__declspec(dllexport) bool Initialize(SRendererDesc &a_Desc) final;
			__declspec(dllexport) void Render() final;

		};
	}
}