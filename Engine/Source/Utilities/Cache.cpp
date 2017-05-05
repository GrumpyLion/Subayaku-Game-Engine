#include "Cache.h"
#include "Utilities\Utilities.h"

namespace Core
{
	void Cache::Shutdown()
	{
		for (auto &temp : m_Textures)
		{
			delete temp.second;
		}
		m_Textures.clear();

		for (auto &temp : m_Meshes)
		{
			delete temp.second;
		}
		m_Meshes.clear();

		delete m_RenderFactory;
	}
	
	void Cache::Initialize(Graphics::IRenderFactory *a_Factory)
	{
		m_RenderFactory = a_Factory;
	}

	Graphics::IMesh* Cache::LoadMesh(Graphics::SMeshDesc &a_Desc)
	{
		auto temp = m_Meshes.find(a_Desc.FilePath);

		if (temp != m_Meshes.end())
		{
			return temp->second;
		}
		else
		{
			auto mesh = m_RenderFactory->CreateMesh(a_Desc);
			return m_Meshes[a_Desc.FilePath] = mesh;
		}
	}

	Graphics::ITexture* Cache::LoadTexture(Graphics::STextureDesc &a_Desc)
	{
		auto temp = m_Textures.find(a_Desc.FilePath);
		
		if (temp != m_Textures.end())
		{
			return temp->second;
		}
		else
		{
			auto texture = m_RenderFactory->CreateTexture(a_Desc);
			if (texture == nullptr)
			{
				LogErr("Error while loading Texture File [%s] in Cache\n", a_Desc.FilePath);
				return nullptr;
			}

			return m_Textures[a_Desc.FilePath] = texture;
		}
	}
}