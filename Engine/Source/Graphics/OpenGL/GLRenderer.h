#pragma once

#include "Graphics\Interface\IRenderer.h"
#include <GLEW\Include\glew.h>
#include <gl/gl.h>
#include "GLEntity.h"

#include <unordered_map>

/////////////
// DEFINES //
/////////////
#define WGL_DRAW_TO_WINDOW_ARB         0x2001
#define WGL_ACCELERATION_ARB           0x2003
#define WGL_SWAP_METHOD_ARB            0x2007
#define WGL_SUPPORT_OPENGL_ARB         0x2010
#define WGL_DOUBLE_BUFFER_ARB          0x2011
#define WGL_PIXEL_TYPE_ARB             0x2013
#define WGL_COLOR_BITS_ARB             0x2014
#define WGL_DEPTH_BITS_ARB             0x2022
#define WGL_STENCIL_BITS_ARB           0x2023
#define WGL_FULL_ACCELERATION_ARB      0x2027
#define WGL_SWAP_EXCHANGE_ARB          0x2028
#define WGL_TYPE_RGBA_ARB              0x202B
#define WGL_CONTEXT_MAJOR_VERSION_ARB  0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB  0x2092
#define GL_ARRAY_BUFFER                   0x8892
#define GL_STATIC_DRAW                    0x88E4
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31
#define GL_COMPILE_STATUS                 0x8B81
#define GL_LINK_STATUS                    0x8B82
#define GL_INFO_LOG_LENGTH                0x8B84
#define GL_TEXTURE0                       0x84C0
#define GL_BGRA                           0x80E1
#define GL_ELEMENT_ARRAY_BUFFER           0x8893

typedef BOOL(WINAPI * PFNWGLCHOOSEPIXELFORMATARBPROC) (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats,
	int *piFormats, UINT *nNumFormats);
typedef HGLRC(WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int *attribList);
typedef BOOL(WINAPI * PFNWGLSWAPINTERVALEXTPROC) (int interval);

namespace Graphics
{
	namespace OpenGL
	{
		class GLEntity;

		class GLRenderer : public IRenderer
		{
		private:
			PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
			PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
			PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;
			
			HDC m_HDC{};
			SRendererDesc m_Desc{};
			HGLRC m_Context{};

			std::unordered_map<Scene::CMeshRenderer*, GLEntity*> m_Entities;

		public:
			Scene::CCamera *Camera = nullptr;

			bool Initialize(SRendererDesc &a_Desc) override;
			void Render() override;
			void Shutdown() override;

			void AddRenderable(Scene::CMeshRenderer *a_MeshRenderer) override; 
			void RemoveRenderable(Scene::CMeshRenderer *a_MeshRenderer) override;
			void SetCamera(Scene::CCamera *a_Camera) override;
			Scene::CCamera *GetCamera() override;
		};
	}
}