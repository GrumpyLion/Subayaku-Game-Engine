#pragma once

#include "Graphics\Bases\BaseRenderer.h"
#include <GLEW\Include\glew.h>
#include <GLEW\Include\wglew.h>
#include <gl/gl.h>

#include "OpenGL\BufferContainers\GLShaderBufferGlobal.h"
#include "OpenGL\RenderPasses\GLRenderPass.h"

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

			// Used renderpasses
			//
			std::unordered_map<std::string, std::unique_ptr<GLRenderPass>> m_RenderPasses;

			// Reacts on WINDOW_RESIZE event
			//
			void Resize() final;

		public:
			// Adds an render pass to the pipeline
			// Be careful with the order
			//
			void AddRenderPass(std::string a_Name, std::unique_ptr<GLRenderPass> a_RenderPass);

			GLRenderPass* GetRenderPass(std::string a_Name);

			__declspec(dllexport) ~GLRenderer();
			__declspec(dllexport) GLRenderer(Core::Engine *a_Engine);

			__declspec(dllexport) bool Initialize(SRendererDesc &a_Desc) final;
			__declspec(dllexport) void Render() final;

		};
	}
}