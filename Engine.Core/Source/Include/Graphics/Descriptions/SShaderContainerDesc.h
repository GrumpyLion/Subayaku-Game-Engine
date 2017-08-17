#pragma once

#include <string>
#include "SShaderDesc.h"
#include "Utilities\Utilities.h"
#include "Utilities\FileSystem.h"

namespace Graphics
{
	struct SShaderContainerDesc
	{
		SShaderDesc Vertex{};
		SShaderDesc Fragment{};
		std::string ShaderContainerName;

		void AddShader(std::string a_FilePath)
		{
			std::string GLSLpath = GetShaderLocation(Core::RenderDevice::OpenGL, a_FilePath);

			auto GLSLtemp = Core::FileSystem::StaticClass()->GetFile(GLSLpath);

			//std::string HLSLpath = GetShaderLocation(Core::RenderDevice::DirectX, a_FilePath);

			//auto HLSLtemp = Core::FileSystem::StaticClass()->GetFile(HLSLpath);

			SShaderDesc desc{};
			desc.FilePath = a_FilePath;

			if (GLSLtemp != nullptr)
				desc.GLSLCode = reinterpret_cast<const char*>(GLSLtemp->Data.data());

			//if (HLSLtemp != nullptr)
			//	desc.HLSLCode = reinterpret_cast<const char*>(HLSLtemp->Data.data());

			std::string extension = GetExtension(a_FilePath);
			ToLowerCase(extension);

			if (extension == "vs")
			{
				desc.Type = EShaderType::VertexShader;
				Vertex = desc;
			}
			else if (extension == "fs")
			{
				desc.Type = EShaderType::FragmentShader;
				Fragment = desc;
			}
		}

		bool operator==(const SShaderContainerDesc& a_Other) const
		{
			return (Vertex == a_Other.Vertex &&
					Fragment == a_Other.Fragment);
		}
	};
}

// Added for std::unordered_map
//

namespace std
{
	template<>
	struct hash<Graphics::SShaderContainerDesc>
	{
		std::size_t operator()(const Graphics::SShaderContainerDesc& k) const
		{
			size_t result = 17;

			result += 31 + hash<std::string>()(k.Vertex.FilePath);
			result += 31 + hash<std::string>()(k.Fragment.FilePath);

			return result;
		}
	};
}