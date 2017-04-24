#include "Material.h"
#include "Utilities\Utilities.h"

namespace Graphics
{
	void Material::AddTexture(std::string a_FileName, TextureInfo &a_TextureInfo)
	{
		if (m_Textures.find(a_FileName) != m_Textures.end())
		{
			LogErr("Texture [%s] is already added in Material\n", a_FileName);
			return;
		}
		else
		{
			m_Textures.insert(std::pair<std::string, TextureInfo>(a_FileName, a_TextureInfo));
		}
	}

	void Material::RemoveTexture(std::string a_FileName)
	{
		if (m_Textures.find(a_FileName) == m_Textures.end())
		{
			LogErr("Texture [%s] was not added to the Material\n", a_FileName);
			return;
		}
		else
		{
			m_Textures.erase(a_FileName);
		}
	}

	std::unordered_map<std::string, TextureInfo> Material::GetTextures()
	{
		return m_Textures;
	}
}