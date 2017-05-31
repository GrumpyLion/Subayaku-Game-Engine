#include "GLRenderer.h"

namespace Graphics
{
	namespace OpenGL
	{
		bool GLRenderer::Initialize(SRendererDesc &a_Desc)
		{
			m_Desc = a_Desc;
			m_HDC = GetDC(a_Desc.Handle);

			PIXELFORMATDESCRIPTOR pfd{};
			pfd.nSize = sizeof(pfd);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_DRAW_TO_WINDOW| PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
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

			m_Context = wglCreateContext(m_HDC);
			if (CheckIfPointerIsInvalid(m_Context))
				return false;

			if (wglMakeCurrent(m_HDC, m_Context) == FALSE)
				return false;
			
			GLenum glewinit = glewInit();
			if (glewinit != GLEW_OK) 
				return false;
			
			printf("Initializing OpenGL Renderer..\n");
			printf("%s\n", glGetString(GL_VERSION));

			glViewport(0, 0, a_Desc.Width, a_Desc.Height);
			glFrontFace(GL_CW);
			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);

			glEnable(GL_BLEND); 
			glDepthFunc(GL_LESS);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			//if (Core::Engine::StaticClass()->GetScene() != nullptr)
			//{
			//	if (Core::Engine::StaticClass()->GetScene()->GetRenderables().size() > 0)
			//	{
			//		for (auto &temp : Core::Engine::StaticClass()->GetScene()->GetRenderables())
			//		{
			//			AddRenderable(temp.second->GetEntityDesc(), temp.second);
			//		}
			//	}
			//}

			//if (Core::Engine::StaticClass()->GetScene() != nullptr)
			//{
			//	SetCamera(Core::Engine::StaticClass()->GetScene()->GetCamera());
			//}

			m_Container = std::make_unique<GLShaderBufferContainer>();
			m_Container->Initialize(this);

			return true;
		}

		void GLRenderer::Render()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(1, 1, 1, 1);

			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			m_Container->Bind();

			for (auto &temp : m_Entities)
				temp.second->Render();

			SwapBuffers(m_HDC);
		}

		GLRenderer::~GLRenderer()
		{
			m_Entities.clear();
			
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