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
		EShaderType Type = EShaderType::VertexShader;
		std::string FilePath = "NO DATA";
		std::string GLSLCode = "NO DATA";
		std::string HLSLCode = "NO DATA";

		// Added for std::unordered_map
		//

		bool operator==(const SShaderDesc& a_Other) const
		{
			if (FilePath.data() == nullptr)
				return false;

			if (GLSLCode.data() == nullptr)
				return false;

			if (HLSLCode.data() == nullptr)
				return false;

			return (
					FilePath == a_Other.FilePath &&
					GLSLCode == a_Other.GLSLCode &&
					HLSLCode == a_Other.HLSLCode);
		}
	};

}