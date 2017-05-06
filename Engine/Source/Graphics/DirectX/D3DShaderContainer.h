#pragma once

#include <d3d11.h>
#include <D3Dcompiler.h>

#include <fstream>

#include "Math\Math.h"
#include "D3DHelper.h"
#include "D3DRenderer.h"
#include "Graphics\Interface\IShaderContainer.h"

namespace Graphics
{
	namespace DirectX
	{
		class D3DShaderContainer : public IShaderContainer
		{
		private:
			ID3D11VertexShader *m_VertexShader = nullptr;
			ID3D11PixelShader *m_PixelShader = nullptr;

			D3DRenderer *m_Renderer = nullptr;
			ID3D11InputLayout *m_Layout = nullptr;

		public:			
			~D3DShaderContainer();

			bool Initialize(Material *a_Material) override;

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