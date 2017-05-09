#pragma once

#include <string>

namespace Graphics
{
	
	enum EShaderType
	{
		VertexShader,
		FragmentShader
	};

	struct SShaderDesc
	{
		EShaderType Type;
		std::string FilePath;
	};

}