#include "Graphics\Material.h"
#include "Utilities\Utilities.h"
#include "Core\Engine.h"

#include "Graphics\Interface\ITexture.h"

#include "DirectX\D3DTexture.h"
#include "OpenGL\GLTexture.h"

#include "Graphics\Loaders\BMP.h"
#include "Graphics\Loaders\TGA.h"
#include "Graphics\Loaders\PNG.h"

namespace Graphics
{
	void Material::AddShader(std::string a_FilePath)
	{
		std::string GLSLpath = GetShaderLocation(Core::RenderDevice::OpenGL, a_FilePath);

		auto GLSLtemp = ENGINE_ZIPFILE->GetFile(GLSLpath);

		std::string HLSLpath = GetShaderLocation(Core::RenderDevice::DirectX, a_FilePath);

		auto HLSLtemp = ENGINE_ZIPFILE->GetFile(HLSLpath);

		SShaderDesc desc{};
		desc.FilePath = a_FilePath;
		desc.GLSLCode = reinterpret_cast<const char*>(GLSLtemp->Data.data());
		desc.HLSLCode = reinterpret_cast<const char*>(HLSLtemp->Data.data());

		std::string extension = GetExtension(a_FilePath);
		ToLowerCase(extension);

		if (extension == "vs")
		{
			desc.Type = EShaderType::VertexShader;
			Shaders.Vertex = desc;
		}
		else if (extension == "fs")
		{
			desc.Type = EShaderType::FragmentShader;
			Shaders.Fragment = desc;
		}
	}

	void Material::AddTexture(STextureDesc &a_TextureInfo)
	{
		if (Textures.find(a_TextureInfo.FilePath) != Textures.end())
		{
			LogErr("Texture [%s] is already added in Material\n", a_TextureInfo.FilePath);
			return;
		}
		else
		{
			a_TextureInfo.Filter = TextureFilter;
			
			//Find the correct file ending
			std::string extension = GetExtension(a_TextureInfo.FilePath);
			ToLowerCase(extension);

			if (extension == "tga")
			{
				TGA tga = TGA(a_TextureInfo);
			}
			else if (extension == "bmp")
			{
				BMP tga = BMP(a_TextureInfo);
			}
			else if (extension == "png")
			{
				PNG tga = PNG(a_TextureInfo);
			}

			Textures.insert({ a_TextureInfo.FilePath, a_TextureInfo });
		}
	}

	void Material::RemoveTexture(std::string a_FileName)
	{
		if (Textures.find(a_FileName) == Textures.end())
		{
			LogErr("Texture [%s] was not found\n", a_FileName);
			return;
		}
		else
		{
			Textures.erase(a_FileName);
		}
	}
}