#pragma once

#include "D3DShaderContainer.h"
#include "D3DShaderBuffer.h"
#include "D3DTexture.h"

#include "Graphics\Material.h"
#include "Scene\GameObject\GameObject.h"

#include <unordered_map>
#include <memory>

namespace Graphics
{
	namespace DirectX
	{
		class D3DRenderer;

		class D3DMaterial
		{
		private:
			std::unique_ptr<D3DShaderContainer> m_Container = nullptr;
			D3DRenderer *m_Renderer = nullptr;

			D3DShaderBuffer* m_ObjectBuffer = nullptr;

			std::unordered_map<std::string, D3DTexture*> m_Textures;

			struct ObjectBuffer
			{
				Matrix4f World;
			};

		public:
			bool Initialize(Material *a_Material);
			void Bind(Scene::GameObject *a_GameObject);
			
			D3DShaderContainer *GetContainer();
		};
	}
}