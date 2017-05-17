#include "Cache.h"
#include "Utilities\Utilities.h"

namespace Core
{
	void Cache::Initialize(std::unique_ptr<Graphics::IRenderFactory> a_Factory, std::string a_PathToPak)
	{
		m_ZipFile = std::make_unique<GrumpyZip::ZipFile>();
		m_ZipFile->LoadZipFile(a_PathToPak);
		m_RenderFactory = std::move(a_Factory);
	}
	
	Graphics::IMesh* Cache::LoadMesh(Graphics::SMeshDesc &a_Desc)
	{
		if (a_Desc.FilePath == "")
			return nullptr;

		auto temp = m_Meshes.find(a_Desc.FilePath);

		if (temp != m_Meshes.end())
		{
			return temp->second.get();
		}
		else
		{
			auto mesh = m_RenderFactory->CreateMesh(a_Desc);

			m_Meshes[a_Desc.FilePath] = std::move(mesh);
			
			return m_Meshes[a_Desc.FilePath].get();
		}
	}

	Graphics::ITexture* Cache::LoadTexture(Graphics::STextureDesc &a_Desc)
	{
		if (a_Desc.FilePath == "")
			return nullptr;

		auto temp = m_Textures.find(a_Desc.FilePath);
		
		if (temp != m_Textures.end())
		{
			return temp->second.get();
		}
		else
		{
			auto texture = m_RenderFactory->CreateTexture(a_Desc);

			if (texture == nullptr)
			{
				LogErr("Error while loading Texture File [%s] in Cache\n", a_Desc.FilePath);
				return nullptr;
			}

			m_Textures[a_Desc.FilePath] = std::move(texture);

			return m_Textures[a_Desc.FilePath].get();
		}
	}

	Graphics::IShader* Cache::LoadShader(Graphics::SShaderDesc &a_Desc)
	{
		if (a_Desc.FilePath == "")
			return nullptr;

		auto temp = m_Shaders.find(a_Desc.FilePath);

		if (temp != m_Shaders.end())
		{
			return temp->second.get();
		}
		else
		{
			auto container = m_RenderFactory->CreateShader(a_Desc);

			if (container == nullptr)
			{
				LogErr("Error while loading Shader File [%s] in Cache\n", a_Desc.FilePath);
				return nullptr;
			}

			m_Shaders[a_Desc.FilePath] = std::move(container);

			return m_Shaders[a_Desc.FilePath].get();
		}
	}


	Graphics::IShaderBuffer* Cache::LoadShaderBuffer(Graphics::SShaderBufferDesc &a_Desc)
	{
		auto temp = m_ShaderBuffers.find(a_Desc.BufferName);

		if (temp != m_ShaderBuffers.end())
		{
			return temp->second.get();
		}
		else
		{
			auto container = m_RenderFactory->CreateShaderBuffer(a_Desc);

			if (container == nullptr)
			{
				LogErr("Error while loading Shaderbuffer [%s] in Cache\n", a_Desc.BufferName);
				return nullptr;
			}

			m_ShaderBuffers[a_Desc.BufferName] = std::move(container);

			return m_ShaderBuffers[a_Desc.BufferName].get();
		}
	}

	GrumpyZip::ZipFile* Cache::GetZipFile()
	{
		return m_ZipFile.get();
	}
}