#pragma once

#include "Graphics\Material.h"
#include "Math\Math.h"

namespace Graphics
{
	class IShaderContainer
	{
	public:
		virtual ~IShaderContainer() {}

		virtual bool Initialize(Material *a_Material) = 0;

		virtual void BindProgram() = 0;
		virtual void UnbindProgram() = 0;
		virtual bool GetError() = 0;
		
		virtual bool SetInt(const char* a_UniformName, const int a_Value) = 0;
		virtual bool SetFloat(const char* a_UniformName, const float a_Value) = 0;
		virtual bool SetVector2f(const char* a_UniformName, const Vector2f &a_Vec) = 0;
		virtual bool SetVector3f(const char* a_UniformName, const Vector3f &a_Vec) = 0;
		virtual bool SetMatrix4f(const char* a_UniformName, Matrix4f &a_Mat) = 0;
	};
}