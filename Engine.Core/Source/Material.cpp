#include "Graphics\Material.h"
#include "Utilities\Utilities.h"
#include "Utilities\FileSystem.h"

#include "Graphics\Interfaces\ITexture.h"

namespace Graphics
{
	void Material::AddShader(EShaderStage a_Stage, std::string a_FilePath)
	{
		SShaderContainerDesc temp{};

		if (Shaders.find(a_Stage) == Shaders.end())
		{
			temp.AddShader(a_FilePath);
			Shaders.insert({ a_Stage, temp });
		}
		else
		{
			Shaders[a_Stage].AddShader(a_FilePath);
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