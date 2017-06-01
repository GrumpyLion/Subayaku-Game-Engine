#pragma once

#include "Graphics\Enums\TextureEnums.h"
#include "Graphics\Descriptions\STextureDesc.h"
#include "Graphics\Descriptions\SMeshDesc.h"
#include "Utilities\Utilities.h"
#include <GLEW\Include\glew.h>

namespace Graphics
{
	namespace OpenGL
	{
		inline GLenum ActiveTextureIndex(int index)
		{
			switch (index)
			{
			case 0:
				return GL_TEXTURE0;
				break;
			
			case 1:
				return GL_TEXTURE1;
				break;

			case 2:
				return GL_TEXTURE2;
				break;

			case 3:
				return GL_TEXTURE3;
				break;

			case 4:
				return GL_TEXTURE4;
				break;

			case 5:
				return GL_TEXTURE5;
				break;

			case 6:
				return GL_TEXTURE6;
				break;

			case 7:
				return GL_TEXTURE7;
				break;

			case 8:
				return GL_TEXTURE8;
				break;

			case 9:
				return GL_TEXTURE9;
				break;

			default:
				LogErr("Error Active Texture index is to high !");
			}
			return 0;
		}

		inline GLenum EMeshPrimitiveToGL(EMeshPrimitive &a_Primitive)
		{
			GLenum mode;
			switch (a_Primitive)
			{
			case EMeshPrimitive::TRIANGLES:
				mode = GL_TRIANGLES;
				break;

			case EMeshPrimitive::TRIANGLE_STRIP:
				mode = GL_TRIANGLE_STRIP;
				break;

			case EMeshPrimitive::LINES:
				mode = GL_LINES;
				break;

			case EMeshPrimitive::TRIANGLE_FAN:
				mode = GL_TRIANGLE_FAN;
				break;

			case EMeshPrimitive::POINTS:
				mode = GL_POINTS;
				break;
			}
			return mode;
		}

		inline GLenum ETextureFormatToGL(ETextureFormat &a_Format)
		{
			GLenum format;

			switch (a_Format)
			{
			case ETextureFormat::RGBA:
				format = GL_RGBA;
				break;

			case ETextureFormat::RGB:
				format = GL_RGB;
				break;

			case ETextureFormat::RG:
				format = GL_RG;
				break;

			case ETextureFormat::R:
				format = GL_R;
				break;

			case ETextureFormat::BGR:
				format = GL_BGR;

			case ETextureFormat::BGRA:
				format = GL_BGRA;
				break;
			}

			return format;
		}

		inline GLenum ETextureFilterToGL(ETextureFilter &a_Filter)
		{
			GLenum filter;

			switch (a_Filter)
			{

			case ETextureFilter::NEAREST:
				filter = GL_NEAREST;
				break;

			case ETextureFilter::LINEAR:
				filter = GL_LINEAR;
				break;
			}

			return filter;
		}

		inline GLenum EMeshPrimitiveToGL(SMeshDesc &a_Desc)
		{
			return EMeshPrimitiveToGL(a_Desc.Mode);
		}

		inline GLenum ETextureFormatToGL(STextureDesc &a_Desc)
		{
			return ETextureFormatToGL(a_Desc.Format);
		}

		inline GLenum ETextureFilterToGL(STextureDesc &a_Desc)
		{
			return ETextureFilterToGL(a_Desc.Filter);
		}
	}
}