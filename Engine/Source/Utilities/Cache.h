#pragma once

#include <unordered_map>
#include <string>

#include "Graphics\Cache\STextureDesc.h"
#include "Graphics\Cache\SMeshDesc.h"

#include "Graphics\Interface\IRenderFactory.h"
#include "Graphics\Interface\IMesh.h"
#include "Graphics\Interface\IShaderContainer.h"
#include "Graphics\Interface\ITexture.h"

namespace Core
{
	class Cache
	{
	private:
		std::unordered_map<std::string, Graphics::ITexture*> m_Textures;
		std::unordered_map<std::string, Graphics::IMesh*> m_Meshes;
		std::unordered_map<std::string, Graphics::IShaderContainer*> m_ShaderContainers;

		Graphics::IRenderFactory *m_RenderFactory = nullptr;

	public:
		void Shutdown();
		void Initialize(Graphics::IRenderFactory *a_Factory);
		
		Graphics::ITexture* LoadTexture(Graphics::STextureDesc &a_Desc);
		Graphics::IMesh* LoadMesh(Graphics::SMeshDesc &a_Desc);

	};
}