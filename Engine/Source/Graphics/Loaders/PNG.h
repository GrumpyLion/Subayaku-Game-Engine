#pragma once

#include <stdio.h>
#include "Utilities\Cache.h"
#include "Core\Engine.h"
#include "Graphics\Cache\STextureDesc.h"

//http://www.libpng.org/pub/png/spec/1.2/png-1.2.pdf
//https://www.w3.org/TR/PNG/

namespace Graphics
{

#pragma pack(push, 1)

	struct HeaderChunk
	{
		std::uint16_t Width;
		std::uint16_t Height;
		std::uint8_t BitDepth;
		std::uint8_t ColorType;
		std::uint8_t CompressionMethod;
		std::uint8_t FilterMethod;
		std::uint8_t InterlaceMethod;
	};

	struct GammaChunk
	{
		std::uint32_t Gamma;
	};

	struct SRGBChunk
	{
		std::uint8_t Intent;
	};

	struct PHYSChunk
	{
		std::uint32_t UnitsX;
		std::uint32_t UnitsY;
		std::uint8_t UnitSpecifier;
	};

	struct TEXTChunk
	{
		std::string Text;
	};

#pragma pack(pop)

	class PNG
	{
	public:
		PNG(STextureDesc &a_Desc)
		{
			auto temp = Core::Engine::StaticClass()->GetCache()->GetZipFile()->GetFile(a_Desc.FilePath);

			std::uint8_t header[8] = { 0 };
			std::uint8_t headerSignature[8] = { 137, 80, 78, 71, 13, 10, 26, 10 };
			std::uint32_t fileHead = 0;
			std::uint32_t dataHead = 0;

			std::vector<unsigned char> data;

			memcpy(&header, &temp->Data[fileHead], sizeof(header));
			fileHead += 8;

			//Check if the header is correct
			if (!std::memcmp(&header, &headerSignature, sizeof(header)))
			{
				while (fileHead < temp->Data.size())
				{
					std::uint32_t chunkSize = (std::uint32_t)temp->Data[fileHead+3];
					fileHead += 4;

					//A PNG file is build up on chunks
					//The first one SHOULD be a header chunk
					if (std::memcmp("IHDR", &temp->Data[fileHead], 4) == 0)
					{
						if (chunkSize == 0)
						{
							printf("IHDR: Chunksize zero\n");
							fileHead += sizeof(HeaderChunk) + 4;
							continue;
						}

						HeaderChunk hChunk; // (HeaderChunk*)&temp->Data[fileHead]
						memcpy(&hChunk, &temp->Data[fileHead], sizeof(HeaderChunk));
						fileHead += sizeof(HeaderChunk) + 4;
					}
					//Data chunk
					else if (std::memcmp("IDAT", &temp->Data[fileHead], 4) == 0)
					{
						if (chunkSize == 0)
						{
							printf("IDAT: Chunksize zero\n");
							continue;
						}
						printf("IDAT: Chunksize %i\n", chunkSize);
						
						data.resize(data.size() + chunkSize);
						memcpy(&data[dataHead], &temp->Data[fileHead+4], chunkSize);
						dataHead += chunkSize;

						fileHead += chunkSize + 4;
					}
					//End of file chunk
					else if (std::memcmp("IEND", &temp->Data[fileHead], 4) == 0)
					{
						a_Desc.PixelData = data;
						a_Desc.Width = 256;
						a_Desc.Height = 256;
						a_Desc.Format = ETextureFormat::RGB;
						return;
					}
					else if (std::memcmp("sRGB", &temp->Data[fileHead], 4) == 0)
					{
						SRGBChunk *chunk = (SRGBChunk*)&temp->Data[fileHead];
						fileHead += sizeof(SRGBChunk) + 4;
					}
					else if (std::memcmp("gAMA", &temp->Data[fileHead], 4) == 0)
					{
						fileHead += sizeof(GammaChunk) + 4;
					}
					else if (std::memcmp("pHYs", &temp->Data[fileHead], 4) == 0)
					{
						PHYSChunk *chunk = (PHYSChunk*)&temp->Data[fileHead];
						fileHead += sizeof(PHYSChunk) + 4;
					}
					//Text Chunk has comments
					else if (std::memcmp("tEXt", &temp->Data[fileHead], 4) == 0)
					{
						TEXTChunk text;
						text.Text.resize(chunkSize);
						memcpy(&text.Text[0], &temp->Data[fileHead], chunkSize);
						printf("%s", text.Text.c_str());

						fileHead += chunkSize + 4;
					}
				}
			}

		}
	};
}