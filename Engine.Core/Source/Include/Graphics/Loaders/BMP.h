#pragma once

#include "Utilities\Utilities.h"

#include <Windows.h>
#include <vector>

#include "Core\Engine.h"
#include "Graphics\Descriptions\STextureDesc.h"

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
			auto temp = Core::Engine::StaticClass()->ZipFile->GetFile(a_TextureData.FilePath);

			if (temp == nullptr)
				throw std::invalid_argument("Error: File Not Found.");

			//Getting the file size
			std::size_t Length = temp->FileSize;

			std::vector<std::uint8_t> FileInfo(Length);

 			memcpy(FileInfo.data(), &temp->Data[0], 54);

			if (FileInfo[0] != 'B' && FileInfo[1] != 'M')
			{
				throw std::invalid_argument("Error: Invalid File Format. Bitmap Required.");
			}

			if (FileInfo[28] != 24 && FileInfo[28] != 32)
			{
				throw std::invalid_argument("Error: Invalid File Format. 24 or 32 bit Image Required.");
			}

			BitsPerPixel = FileInfo[28];
			
			Width = FileInfo[18] + (FileInfo[19] << 8);
			Height = FileInfo[22] + (FileInfo[23] << 8);
			
			std::uint32_t PixelsOffset = FileInfo[10] + (FileInfo[11] << 8);
			std::uint32_t size = ((Width * BitsPerPixel + 31) / 32) * 4 * Height;
			
			Pixels.resize(size);
			memcpy(Pixels.data(), &temp->Data[PixelsOffset], size);
			
			a_TextureData.PixelData = Pixels;
			a_TextureData.Format = ETextureFormat::BGR;
			a_TextureData.Width = Width;
			a_TextureData.Height = Height;
		}
	};
}