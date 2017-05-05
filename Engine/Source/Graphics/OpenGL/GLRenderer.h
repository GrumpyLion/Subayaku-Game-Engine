#pragma once

#include "Graphics\Interface\IRenderer.h"
#include <GLEW\Include\glew.h>
#include <gl/gl.h>
#include "GLEntity.h"

#include <unordered_map>

namespace Graphics
{
	namespace OpenGL
	{
		class GLEntity;

		class GLRenderer : public IRenderer
		{
		private:
			HDC m_HDC{};
			SRendererDesc m_Desc{};
			HGLRC m_Context{};

			std::unordered_map<Scene::CMeshRenderer*, GLEntity*> m_Entities;

		public:
			Scene::CCamera *Camera = nullptr;

			bool Initialize(SRendererDesc &a_Desc) override;
			void Render() override;
			void Shutdown() override;

			void AddRenderable(Scene::CMeshRenderer *a_MeshRenderer) override; 
			void RemoveRenderable(Scene::CMeshRenderer *a_MeshRenderer) override;
			void SetCamera(Scene::CCamera *a_Camera) override;
			Scene::CCamera *GetCamera() override;
		};
	}
}