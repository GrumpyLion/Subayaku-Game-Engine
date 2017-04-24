#pragma once

#include <string>
#include <unordered_map>

#include "TextureInfo.h"

namespace Graphics
{
	class Material
	{
	private:
		std::unordered_map<std::string, TextureInfo> m_Textures;
	
	public:
		void AddTexture(std::string a_FileName, TextureInfo &a_TextureInfo);
		void RemoveTexture(std::string a_FileName);
		std::unordered_map<std::string, TextureInfo> GetTextures();

		std::string VertexShader = "";
		std::string FragmentShader = "";
	};
}