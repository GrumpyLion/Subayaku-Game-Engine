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
		//TODO MOVE
		struct MatrixBufferType
		{
			Matrix4f World;
			Matrix4f View;
			Matrix4f Projection;
		};

		class D3DShaderContainer : public IShaderContainer
		{
		private:
			ID3D11VertexShader *m_VertexShader = nullptr;
			ID3D11PixelShader *m_PixelShader = nullptr;

			D3DRenderer *m_Renderer = nullptr;
			ID3D11SamplerState* m_SampleState = nullptr;
			ID3D11InputLayout *m_Layout = nullptr;

		public:
			ID3D11Buffer *m_MatrixBuffer = nullptr;
			
			~D3DShaderContainer();

			bool Initialize(Material *a_Material) override;

			void BindProgram() override;
			void UnbindProgram() override;
			bool GetError() override;
			
			bool SetInt(const char* a_UniformName, const int a_Value) override;
			bool SetFloat(const char* a_UniformName, const float a_Value) override;
			bool SetVector2f(const char* a_UniformName, const Vector2f &a_Vec) override;
			bool SetVector3f(const char* a_UniformName, const Vector3f &a_Vec) override;
			bool SetMatrix4f(const char* a_UniformName, Matrix4f &a_Mat) override;
		};
	}
}