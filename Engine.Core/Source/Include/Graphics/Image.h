#pragma once

#include <string>
#include "Math\Math.h"
#include "Graphics\Descriptions\STextureDesc.h"

namespace Graphics
{
	class Image
	{
	private:
		Graphics::STextureDesc m_Desc{};

	public:
		Image(std::string a_Path);

		Vector3f GetPixelAt(int a_X, int a_Y);
	};
}