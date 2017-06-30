#include "Graphics\Image.h"

#include "Graphics\Loaders\TGA.h"

namespace Graphics
{
	Image::Image(std::string a_Path)
	{		
		m_Desc.FilePath = a_Path;

		TGA tga = TGA(m_Desc);
	}

	Vector3f Image::GetPixelAt(int a_X, int a_Y)
	{
		Vector3f temp;

		switch (m_Desc.Format)
		{
		case ETextureFormat::BGRA:
 			temp.x = m_Desc.PixelData[a_X * 4 + 2 + abs(a_Y - m_Desc.Height) * m_Desc.Width * 4];
			temp.y = m_Desc.PixelData[a_X * 4 + 1 + abs(a_Y - m_Desc.Height) * m_Desc.Width * 4];
			temp.z = m_Desc.PixelData[a_X * 4 + abs(a_Y - m_Desc.Height) * m_Desc.Width * 4];
			break;

		case ETextureFormat::RGB:
			temp.x = m_Desc.PixelData[a_X + a_Y * m_Desc.Width];
			temp.y = m_Desc.PixelData[a_X + 1 + a_Y * m_Desc.Width];
			temp.z = m_Desc.PixelData[a_X + 2 + a_Y * m_Desc.Width];
			break;
		}

		return temp;
	}
}