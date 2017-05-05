#pragma once

#include <string>
#include <unordered_map>

#include "Graphics\Cache\STextureDesc.h"

namespace Graphics
{
	class Material
	{
	private:
		std::unordered_map<std::string, STextureDesc> m_Textures;
		std::unordered_map<std::string, float> m_FloatUniforms;
		
	public:
		void AddTexture(STextureDesc &a_TextureInfo);
		void RemoveTexture(std::string a_FileName);

		void AddFloatUniform(std::string a_UniformName, float a_Value);
		void RemoveFloatUniform(std::string a_UniformName);

		std::unordered_map<std::string, STextureDesc> GetTextures();
		std::unordered_map<std::string, float> GetFloats();

		std::string VertexShader = "";
		std::string FragmentShader = "";
	};
}