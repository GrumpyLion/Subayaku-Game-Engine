#pragma once

#include "Utilities\Utilities.h"

#include <Windows.h>
#include <fstream>
#include <gl\GL.h>
#include <vector>
#include "Graphics\Cache\STextureDesc.h"

namespace Graphics
{
	class BMP
	{
	public:
		std::uint32_t Width, Height;
		std::uint16_t BitsPerPixel;
		std::vector<std::uint8_t> Pixels;
		

		BMP(STextureDesc &a_TextureData)
		{
			std::fstream hFile(a_TextureData.FilePath, std::ios::in | std::ios::binary);
			if (!hFile.is_open()) throw std::invalid_argument("Error: File Not Found.");

			//Getting the file size
			hFile.seekg(0, std::ios::end);
			std::size_t Length = hFile.tellg();

			//Setting the pointer back to the beginning
			hFile.seekg(0, std::ios::beg);
			std::vector<std::uint8_t> FileInfo(Length);
			hFile.read(reinterpret_cast<char*>(FileInfo.data()), 54);

			if (FileInfo[0] != 'B' && FileInfo[1] != 'M')
			{
				hFile.close();
				throw std::invalid_argument("Error: Invalid File Format. Bitmap Required.");
			}

			if (FileInfo[28] != 24 && FileInfo[28] != 32)
			{
				hFile.close();
				throw std::invalid_argument("Error: Invalid File Format. 24 or 32 bit Image Required.");
			}

			BitsPerPixel = FileInfo[28];
			Width = FileInfo[18] + (FileInfo[19] << 8);
			Height = FileInfo[22] + (FileInfo[23] << 8);
			std::uint32_t PixelsOffset = FileInfo[10] + (FileInfo[11] << 8);
			std::uint32_t size = ((Width * BitsPerPixel + 31) / 32) * 4 * Height;
			Pixels.resize(size);

			hFile.seekg(PixelsOffset, std::ios::beg);
			hFile.read(reinterpret_cast<char*>(Pixels.data()), size);
			hFile.close();

			a_TextureData.PixelData = Pixels;
			a_TextureData.Format = ETextureFormat::BGR;
			a_TextureData.Width = Width;
			a_TextureData.Height = Height;
		}
	};
}