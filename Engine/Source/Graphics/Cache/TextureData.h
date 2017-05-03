#pragma once

#include "Graphics\Cache\TextureEnums.h"

namespace Graphics
{
	class TextureData
	{
	private:
	
	public:
		unsigned char* PixelData;
		ETextureFormat Format;
		int Width = 0, Height = 0;
		
		~TextureData()
		{
			delete[] PixelData;
		}

		void Initialize(unsigned char* a_PixelData, ETextureFormat a_Format, int a_Width, int a_Height)
		{
			Width = a_Width;
			Height = a_Height;

			PixelData = a_PixelData;
			Format = a_Format;
		}
	};
}