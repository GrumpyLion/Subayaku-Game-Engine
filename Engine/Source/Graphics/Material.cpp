#include "Material.h"
#include "Utilities\Utilities.h"

namespace Graphics
{
	void Material::AddFloatUniform(std::string a_UniformName, float a_Value)
	{
		if (m_FloatUniforms.find(a_UniformName) != m_FloatUniforms.end())
		{
			LogErr("Float Uniform [%s] is already added\n");
			return;
		}
		else
		{
			m_FloatUniforms.insert({ a_UniformName, a_Value });
		}
	}

	void Material::RemoveFloatUniform(std::string a_UniformName)
	{
		if (m_FloatUniforms.find(a_UniformName) == m_FloatUniforms.end())
		{
			LogErr("Float Uniform [%s] was not found\n", a_UniformName);
			return;
		}
		else
		{
			m_FloatUniforms.erase(a_UniformName);
		}
	}

	void Material::AddTexture(STextureDesc &a_TextureInfo)
	{
		if (m_Textures.find(a_TextureInfo.FilePath) != m_Textures.end())
		{
			LogErr("Texture [%s] is already added in Material\n", a_TextureInfo.FilePath);
			return;
		}
		else
		{
			a_TextureInfo.Filter = TextureFilter;
			m_Textures.insert({ a_TextureInfo.FilePath, a_TextureInfo });
		}
	}

	void Material::RemoveTexture(std::string a_FileName)
	{
		if (m_Textures.find(a_FileName) == m_Textures.end())
		{
			LogErr("Texture [%s] was not found\n", a_FileName);
			return;
		}
		else
		{
			m_Textures.erase(a_FileName);
		}
	}

	std::unordered_map<std::string, STextureDesc> Material::GetTextures()
	{	return m_Textures;	}


	std::unordered_map<std::string, float> Material::GetFloats()
	{	return m_FloatUniforms;	}
}