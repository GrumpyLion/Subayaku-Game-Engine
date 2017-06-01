#pragma once

#include <fstream>
#include <stdio.h>
#include <string>

#include "Graphics\Descriptions\STextureDesc.h"
#include "Core\Engine.h"

//Used help from this site
//http://www.paulbourke.net/dataformats/tga/

namespace Graphics
{

#pragma pack(push, 1)

	struct TGAHeader
	{
		char IDLength;
		char ColorMapType;
		char DataTypeCode;
		short ColorMapOrigin;
		short ColorMapLength;
		char ColorMapDepth;
		short XOrigin;
		short YOrigin;
		short Width;
		short Height;
		char BitsPerPixel;
		char ImageDescriptor;
	};

#pragma pack(pop)

	class TGA
	{
	public:
		TGA(STextureDesc &a_Desc)
		{
			auto file = Core::Engine::StaticClass()->ZipFile->GetFile(a_Desc.FilePath);
			
			//Check if the compiler added padding bytes
			if (sizeof(TGAHeader) != 18)
			{
				printf("Error TGAHeader has a wrong size. Compiler has added padding bytes!\n");
				return;
			}

			//Load the header
			TGAHeader *header = (TGAHeader*)&file->Data[0];



			std::vector<std::uint8_t> resultingData;
			
			//Data is compressed
			if (header->DataTypeCode == 10)
			{
				a_Desc.Width = header->Width;
				a_Desc.Height = header->Height;

				std::uint32_t size = (a_Desc.Width + 32) * 4 * a_Desc.Height;

				//Load the data
				resultingData.resize(size);

				std::uint32_t fileHead = 18;
				std::uint32_t currentPixel = 0;
				std::uint32_t currentByte = 0;
				std::uint8_t chunkHead = 0;
				std::uint8_t bytesPerPixel = header->BitsPerPixel / 8;
				
				while (currentPixel < (unsigned int)(a_Desc.Width * a_Desc.Height))
				{
					memcpy(&chunkHead, &file->Data[fileHead], sizeof(unsigned char));
					fileHead += sizeof(unsigned char);

					std::uint8_t type = (chunkHead & 0x80);
					std::uint8_t count = (chunkHead & 0x7F) + 1;

					//If its a raw packet
					if (type == 0)
					{
						//just copy
						if (header->BitsPerPixel == 32)
						{
							memcpy(&resultingData[currentByte], &file->Data[fileHead], sizeof(unsigned char) * bytesPerPixel * count);

							currentByte += bytesPerPixel * count;
							currentPixel += count;
							fileHead += bytesPerPixel * count;
						}
						else
						{
							for (int i = 0; i < count; i++, currentPixel++)
							{
								resultingData[currentByte++] = file->Data[fileHead + 0];
								resultingData[currentByte++] = file->Data[fileHead + 1];
								resultingData[currentByte++] = file->Data[fileHead + 2];
								resultingData[currentByte++] = (header->BitsPerPixel == 24) ? 255 : file->Data[fileHead + 3];

								fileHead += bytesPerPixel;
							}
						}
					}
					else
					{
						//If its a run length packet then copy the same pixel n times
						for (int i = 0; i < count; i++, currentPixel++)
						{
							resultingData[currentByte++] = file->Data[fileHead + 0];
							resultingData[currentByte++] = file->Data[fileHead + 1];
							resultingData[currentByte++] = file->Data[fileHead + 2];
							resultingData[currentByte++] = (header->BitsPerPixel == 24) ? 255 : file->Data[fileHead + 3];
						}
						fileHead += bytesPerPixel;
					}
				}
			}
			//Data is uncompressed
			else if (header->DataTypeCode == 2)
			{
				a_Desc.Width = header->Width;
				a_Desc.Height = header->Height;

				std::uint32_t size = (a_Desc.Width * 4) * a_Desc.Height;

				//Load the data
				resultingData.resize(file->FileSize - sizeof(TGAHeader));

				//The image should have 32 bits if not we will just add full alpha (slow)
				if(header->BitsPerPixel == 32)
					memcpy(&resultingData[0], &file->Data[18], file->FileSize - sizeof(TGAHeader));
				else
				{
					resultingData.resize(size);

					unsigned int currentPixel = 0;
					for (int i = 18; i < file->Data.size() - 3; i += 3)
					{
						resultingData[currentPixel++] = file->Data[i+2];
						resultingData[currentPixel++] = file->Data[i+1];
						resultingData[currentPixel++] = file->Data[i];
						resultingData[currentPixel++] = (unsigned char)255;
					}
				}
			}

			//Because of DX11 we only can have BGRA
			a_Desc.Format = ETextureFormat::BGRA;
			a_Desc.PixelData = resultingData;
		}
	};
}