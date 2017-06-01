#pragma once

#include "Graphics\Descriptions\SShaderContainerDesc.h"
#include "Graphics\Interfaces\IShaderContainer.h"
#include "D3DShader.h"

#include <memory>

namespace Graphics
{
	namespace DirectX
	{
		class D3DRenderer;
		class D3DShader;

		class D3DShaderContainer : public IShaderContainer
		{
		private:
			ID3D11InputLayout *m_Layout = nullptr;
			D3DRenderer *m_Renderer = nullptr;

			D3DShader *m_VertexShader;
			D3DShader *m_FragmentShader;

		public:			
			~D3DShaderContainer();

			bool Initialize(SShaderContainerDesc &a_Desc, IRenderer *a_Renderer) override;

			void BindProgram() override;
			void UnbindProgram() override;
			bool GetError() override;
			
			bool SetInt(const char* a_UniformName, const int a_Value);
			bool SetFloat(const char* a_UniformName, const float a_Value);
			bool SetVector2f(const char* a_UniformName, const Vector2f &a_Vec);
			bool SetVector3f(const char* a_UniformName, const Vector3f &a_Vec);
			bool SetMatrix4f(const char* a_UniformName, Matrix4f &a_Mat);
		};
	}
}