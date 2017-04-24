#pragma once

#include <unordered_map>
#include <string>
#include "TextureData.h"
#include "Utilities\Utilities.h"

//Loaders
#include "Graphics\Loaders\BMPLoader.h"

namespace Graphics
{
	class TextureCache
	{
	private:
		std::unordered_map<std::string, TextureData<unsigned char*>*> m_Textures{};

	public:
		~TextureCache()
		{
			for (auto &temp : m_Textures)
			{
				delete temp.second;
			}
			m_Textures.clear();
		}

		//This function takes the directory of an image. Loads the image if not already cached.
		//And if its already loaded it will use the cached texture
		TextureData<unsigned char*>* GetTexture(std::string a_FileName)
		{
			if (m_Textures.find(a_FileName) != m_Textures.end())
			{
				TextureData<unsigned char*> *temp = m_Textures.find(a_FileName)->second;
				if (temp == nullptr)
				{
					LogErr("Cached Texture [%s] is null\n", a_FileName);
					return nullptr;
				}
				return temp;
			}
			else
			{
				TextureData<unsigned char*> *temp;

				BMPLoader loader = BMPLoader();
				if (!loader.LoadFile(a_FileName.c_str(), temp))
					return nullptr;		

				m_Textures.insert(std::pair<std::string, TextureData<unsigned char*>*>(a_FileName, temp));
				return temp;
			}
		}
	};
}