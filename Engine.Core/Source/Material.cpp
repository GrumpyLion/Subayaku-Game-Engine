#include "Graphics\Material.h"
#include "Utilities\Utilities.h"
#include "Utilities\FileSystem.h"

#include "Graphics\Interfaces\ITexture.h"

namespace Graphics
{
	void Material::AddShader(std::string a_FilePath)
	{
		Shaders.AddShader(a_FilePath);
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