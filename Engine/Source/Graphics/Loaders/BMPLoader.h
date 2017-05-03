#pragma once

#include "Utilities\Utilities.h"

#include <Windows.h>
#include <fstream>
#include <gl\GL.h>
#include "Graphics\Cache\TextureData.h"

namespace Graphics
{
	class BMPLoader
	{
	public:
		unsigned char* m_PixelData = nullptr;

		int m_Width = 0, m_Height = 0;

		bool LoadFile(const char* a_FileName, TextureData*& a_TextureData)
		{
			unsigned char* bigBuffer = nullptr;

			BITMAPFILEHEADER *bmpHeader = nullptr;
			BITMAPINFOHEADER *bmpInfo = nullptr;

			//std::ios::ate sets the pointer to the end
			std::ifstream fileStream(a_FileName, std::ios::binary | std::ios::ate);
			if (!fileStream)
			{
				printf("Error: could't open file %s\n", a_FileName);
				return false;
			}

			//tellg gives the current pointer
			int fileSize = (int)fileStream.tellg();

			//Reset the file pointer to 0 because we're right now at the last position (std::ios::ate)
			fileStream.seekg(0);

			bigBuffer = new unsigned char[fileSize];

			fileStream.read((char*)bigBuffer, fileSize);

			// length = get file size
			// buffer = new [length]
			// bmpHeader = (...)buffer
			// bmpInfo = (...)(buffer+sizeof(HEADER))
			// data = (...)(buffer+sizeof(HEADER)+sizeof(INFO))

			//Read the header data 

			bmpHeader = (BITMAPFILEHEADER*)bigBuffer;
			bmpInfo = (BITMAPINFOHEADER*)(bigBuffer + sizeof(BITMAPFILEHEADER));

			//Check if the file is really bmp file format
			if (bmpHeader->bfType != 0x4D42)
			{
				printf("This File isn't a bitmap\n");
				return false;
			}

			//Allocate data for pixels
			unsigned char *oldPixelData = (bigBuffer + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER));

			unsigned int pixelCount = fileSize - (sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER));
			m_PixelData = new unsigned char[bmpInfo->biWidth * bmpInfo->biHeight * 4];

			//Since loaded data is in BGR we change it to RGB
			unsigned char tmpRGB = 0;
			int j = 0;

			m_Width = bmpInfo->biWidth;
			m_Height = bmpInfo->biHeight;

			for (unsigned int i = 0; i < pixelCount; i += 3)
			{
				m_PixelData[j] = oldPixelData[i+2];
				m_PixelData[j + 1] = oldPixelData[i + 1];
				m_PixelData[j + 2] = oldPixelData[i];
				m_PixelData[j + 3] = 255; //Full opacity
				j += 4;
			}
			
			a_TextureData  = new TextureData();
			a_TextureData->Initialize(m_PixelData, ETextureFormat::RGBA, m_Width, m_Height);

			delete[] bigBuffer;
			return true;
		}
	};
}