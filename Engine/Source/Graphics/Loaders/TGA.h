#pragma once

#include "Utilities\Utilities.h"

#include <Windows.h>
#include <vector>

#include "Graphics\Cache\STextureDesc.h"
#include "Core\Engine.h"
#include "Utilities\Cache.h"

namespace Graphics
{
	typedef union PixelInfo
	{
		std::uint32_t Colour;
		struct
		{
			std::uint8_t R, G, B, A;
		};
	} *PPixelInfo;

	class TGA
	{
	private:
		std::vector<std::uint8_t> Pixels;
		bool ImageCompressed;
		std::uint32_t size, BitsPerPixel;

	public:
		std::uint32_t Width, Height;

		TGA(STextureDesc &a_Desc)
		{
			auto temp = Core::Engine::StaticClass()->GetCache()->GetZipFile()->GetFile(a_Desc.FilePath);

			if(temp == nullptr)
				throw std::invalid_argument("File Not Found.");

			std::uint8_t Header[18] = { 0 };
			std::vector<std::uint8_t> ImageData;
			static std::uint8_t DeCompressed[12] = { 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
			static std::uint8_t IsCompressed[12] = { 0x0, 0x0, 0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };

			memcpy(&Header, &temp->Data[0], sizeof(Header));

			int head = sizeof(Header);

			if (!std::memcmp(DeCompressed, &Header, sizeof(DeCompressed)))
			{
				BitsPerPixel = Header[16];
				Width = Header[13] * 256 + Header[12];
				Height = Header[15] * 256 + Header[14];
				size = ((Width * BitsPerPixel + 31) / 32) * 4 * Height;

				if ((BitsPerPixel != 24) && (BitsPerPixel != 32))
				{
					throw std::invalid_argument("Invalid File Format. Required: 24 or 32 Bit Image.");
				}

				ImageData.resize(size);
				ImageCompressed = false;
				memcpy(reinterpret_cast<char*>(ImageData.data()), &temp->Data[head], size);

				head += size;
			}
			else if (!std::memcmp(IsCompressed, &Header, sizeof(IsCompressed)))
			{
				BitsPerPixel = Header[16];
				Width = Header[13] * 256 + Header[12];
				Height = Header[15] * 256 + Header[14];
				//Set the size always to 32 bits we will push 255 if there is no alpha
				size = ((Width * 32 + 31) / 32) * 4 * Height;

				if ((BitsPerPixel != 24) && (BitsPerPixel != 32))
				{
					throw std::invalid_argument("Invalid File Format. Required: 24 or 32 Bit Image.");
				}

				PixelInfo Pixel = { 0 };
				int CurrentByte = 0;
				std::size_t CurrentPixel = 0;
				ImageCompressed = true;
				std::uint8_t ChunkHeader = { 0 };
				int BytesPerPixel = (BitsPerPixel / 8);
				ImageData.resize(Width * Height * sizeof(PixelInfo));

				do
				{
					memcpy(reinterpret_cast<char*>(&ChunkHeader), &temp->Data[head], sizeof(ChunkHeader));
					head += sizeof(ChunkHeader);
					//hFile.read(reinterpret_cast<char*>(&ChunkHeader), sizeof(ChunkHeader));

					if (ChunkHeader < 128)
					{
						++ChunkHeader;
						for (int I = 0; I < ChunkHeader; ++I, ++CurrentPixel)
						{
							memcpy(reinterpret_cast<char*>(&Pixel), &temp->Data[head], BytesPerPixel);
							head += BytesPerPixel;

							ImageData[CurrentByte++] = Pixel.B;
							ImageData[CurrentByte++] = Pixel.G;
							ImageData[CurrentByte++] = Pixel.R;
							if (BitsPerPixel > 24) 
								ImageData[CurrentByte++] = Pixel.A;
							else
								ImageData[CurrentByte++] = 255;
						}
					}
					else
					{
						ChunkHeader -= 127;
						memcpy(reinterpret_cast<char*>(&Pixel), &temp->Data[head], BytesPerPixel);
						head += BytesPerPixel;

						for (int I = 0; I < ChunkHeader; ++I, ++CurrentPixel)
						{
							ImageData[CurrentByte++] = Pixel.B;
							ImageData[CurrentByte++] = Pixel.G;
							ImageData[CurrentByte++] = Pixel.R;
							if (BitsPerPixel > 24) 
								ImageData[CurrentByte++] = Pixel.A;
							else
								ImageData[CurrentByte++] = 255;
						}
					}
				} while (CurrentPixel < (Width * Height));
			}
			else
			{
				throw std::invalid_argument("Invalid File Format. Required: 24 or 32 Bit TGA File.");
			}

			a_Desc.PixelData = ImageData;
			a_Desc.Width = Width;
			a_Desc.Height = Height;
			a_Desc.Format = ETextureFormat::RGBA;

		}

	};
}