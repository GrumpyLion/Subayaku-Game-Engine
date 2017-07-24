#include "OpenGL\GLRenderer.h"

#include "OpenGL\GLEntity.h"
#include "OpenGL\GLTexture.h"
#include "OpenGL\GLMesh.h"
#include "OpenGL\GLShaderBuffer.h"
#include "OpenGL\GLShader.h"

#include "OpenGL\RenderPasses\GLRenderPassGBuffer.h"
#include "OpenGL\RenderPasses\GLRenderPassShadow.h"

#include "Utilities\FileSystem.h"

extern "C"
{
	__declspec(dllexport) Graphics::IRenderer* __stdcall CreateRenderer(Core::Engine *a_Engine)
	{
		Graphics::OpenGL::GLRenderer *renderer = new Graphics::OpenGL::GLRenderer(a_Engine);

		return renderer;
	}
}

namespace Graphics
{
	namespace OpenGL
	{
		GLRenderer::GLRenderer(Core::Engine *a_Engine)
			: BaseRenderer(a_Engine)
		{		}

		bool GLRenderer::Initialize(SRendererDesc &a_Desc)
		{
			//Set Lambdas for the cache. It needs to know the types to create.
			m_Cache->SetTextureCreator(std::function<std::unique_ptr<ITexture>()>([]() { return std::make_unique<GLTexture>(); }));
			m_Cache->SetMeshCreator(std::function<std::unique_ptr<IMesh>()>([]() { return std::make_unique<GLMesh>(); }));
			m_Cache->SetShaderCreator(std::function<std::unique_ptr<IShader>()>([]() { return std::make_unique<GLShader>(); }));
			m_Cache->SetShaderBufferCreator(std::function<std::unique_ptr<IShaderBuffer>()>([]() { return std::make_unique<GLShaderBuffer>(); }));

			m_CreateEntity = std::function<std::unique_ptr<IEntity>()>([]() { return std::make_unique<GLEntity>(); });
			
			m_Desc = a_Desc;
			m_HDC = GetDC(a_Desc.Handle);

			PIXELFORMATDESCRIPTOR pfd{};
			pfd.nSize = sizeof(pfd);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.cColorBits = 32;
			pfd.cDepthBits = 32;
			pfd.iLayerType = PFD_MAIN_PLANE;

			int format = ChoosePixelFormat(m_HDC, &pfd);

			//Format creation failed
			if (format == 0)
				return false;

			if (SetPixelFormat(m_HDC, format, &pfd) == FALSE)
				return false;

			// Temp Context for OpenGL 4.0 init
			//
			HGLRC temp = wglCreateContext(m_HDC);

			if (!temp)
				return false;

			if (!wglMakeCurrent(m_HDC, temp))
				return false;

			// Init
			//
			GLenum glewinit = glewInit();
			if (glewinit != GLEW_OK)
			{
				printf("%s\n", glewGetErrorString(glewinit));
				return false;
			}

			const int attribs[] =
			{
				WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
				WGL_CONTEXT_MINOR_VERSION_ARB, 3,
				WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
				0
			};

			// Delete the temp context
			//
			wglMakeCurrent(nullptr, nullptr);
			wglDeleteContext(temp);

			// Create the real one
			//
			m_Context = wglCreateContextAttribsARB(m_HDC, 0, attribs);

			if (!wglMakeCurrent(m_HDC, m_Context))
				return false;
			
			//wglSwapIntervalEXT(0);

			printf("Initializing OpenGL Renderer..\n");
			printf("%s\n", glGetString(GL_VERSION));

			glViewport(0, 0, a_Desc.Width, a_Desc.Height);
			glFrontFace(GL_CW);
			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);

			// Error while everything
			// Use with care
			//
			//glEnable(GL_BLEND);
			//glDepthFunc(GL_LESS);
			//

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			// RenderPasses Here
			// Need to abstract this
			//
			
			AddRenderPass("Shadow", std::make_unique<GLRenderPassShadow>(this));
			AddRenderPass("GBuffer", std::make_unique<GLRenderPassGBuffer>(this));

			return true;
		}

		void GLRenderer::Render()
		{
			for (auto &temp : m_RenderPasses)
			{
				temp.second->RenderPass();
			}

			SwapBuffers(m_HDC);
		}

		void GLRenderer::Resize()
		{
			for (auto &temp : m_RenderPasses)
			{
				temp.second->Resize();
			}
		}

		void GLRenderer::AddRenderPass(std::string a_Name, std::unique_ptr<GLRenderPass> a_RenderPass)
		{
			if (m_RenderPasses.find(a_Name) == m_RenderPasses.end())
			{
				m_RenderPasses.insert({ a_Name, std::move(a_RenderPass) });
			}
			else
			{
				LogErr("RenderPass already added");
			}
		}

		GLRenderPass* GLRenderer::GetRenderPass(std::string a_Name)
		{
			auto temp = m_RenderPasses.find(a_Name);
			
			if (temp != m_RenderPasses.end())
			{
				return temp->second.get();
			}

			return nullptr;
		}

		GLRenderer::~GLRenderer()
		{
			m_Entities.clear();
			m_RenderPasses.clear();

			wglMakeCurrent(nullptr, nullptr);

			if (m_HDC != nullptr)
			{
				ReleaseDC(m_Desc.Handle, m_HDC);
				m_HDC = nullptr;
			}

			if (m_Context != nullptr)
			{
				wglDeleteContext(m_Context);
				m_Context = nullptr;
			}
		}
	}
}