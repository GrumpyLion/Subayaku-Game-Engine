#pragma once

#include "D3DShaderBuffer.h" 
#include "Math\Math.h"
#include "Graphics\Enums\GlobalIndices.h"
#include <memory>

namespace Graphics
{
	namespace DirectX
	{
		class D3DRenderer;

		class D3DShaderBufferContainer
		{
		private:
			D3DRenderer *m_Renderer = nullptr;
			std::unique_ptr<D3DShaderBuffer> m_ConstantGlobalBuffer;
			std::unique_ptr<D3DShaderBuffer> m_DynamicGlobalBuffer;

			//Standart CBuffer with some neat things
			//16 Bit ALIGNMENT !!
			struct DynamicBuffer
			{
				Matrix4f View;
				Matrix4f Projection;

				//In milliseconds
				float TimeSinceStart;
				Vector3f CameraPosition;
			};

		public:
			void Initialize(D3DRenderer *a_Renderer);
			void Bind();
		};
	}
}