#include "GLRenderer.h"

#include "Utilities\Utilities.h"
#include "GLShaderContainer.h"
#include "Graphics\Material.h"
#include "GLEntity.h"
#include "Scene\GameObject\Components\CMeshRenderer.h"
#include "Core\Engine.h"

#include "Scene\Scene.h"
#include "Scene\GameObject\Components\Transformation.h"

#include <iostream>

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
			if (glewinit != GLEW_OK) {
				std::cout << "GLEW not okay! " << glewinit;
				return false;
			}
			
			printf("Initializing OpenGL Renderer..\n");
			printf("%s\n", glGetString(GL_VERSION));

			glViewport(0, 0, a_Desc.Width, a_Desc.Height);
			glFrontFace(GL_CW);
			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);

			glEnable(GL_BLEND); 
			glDepthFunc(GL_LESS);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			if (Core::Engine::StaticClass()->GetScene() != nullptr)
			{
				if (Core::Engine::StaticClass()->GetScene()->GetRenderables().size() > 0)
				{
					for (auto &temp : Core::Engine::StaticClass()->GetScene()->GetRenderables())
					{
						AddRenderable(temp.second);
					}
				}
			}

			if (Core::Engine::StaticClass()->GetScene() != nullptr)
			{
				SetCamera(Core::Engine::StaticClass()->GetScene()->GetCamera());
			}

			m_Container = new GLShaderBufferContainer();
			m_Container->Initialize(this);

			return true;
		}

		void GLRenderer::Render()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.2f, 0.4f, 0.6f, 1);

			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			m_Container->Bind();

			for (auto &temp : m_Entities)
				temp.second->Render();

			SwapBuffers(m_HDC);
		}

		void GLRenderer::AddRenderable(Scene::CMeshRenderer *a_MeshRenderer)
		{
			if (CheckIfPointerIsInvalid(a_MeshRenderer))
				return;

			if (m_Entities.find(a_MeshRenderer) != m_Entities.end())
			{
				LogErr("CMeshrenderer is already added\n");
				return;
			}

			GLEntity *temp = new GLEntity();
			
			if (!temp->Initialize(a_MeshRenderer->GetMesh(), a_MeshRenderer->GetMaterial(), a_MeshRenderer->Parent))
			{
				LogErr("While trying to add a new Renderable\n");
				SafeDelete(temp);
				return;
			}

			m_Entities.insert({ a_MeshRenderer, temp });
		}

		void GLRenderer::RemoveRenderable(Scene::CMeshRenderer *a_MeshRenderer)
		{
			if (CheckIfPointerIsInvalid(a_MeshRenderer))
				return;

			if (m_Entities.find(a_MeshRenderer) == m_Entities.end())
			{
				LogErr("CMeshrenderer was not found\n");
				return;
			}
			else
			{
				GLEntity *temp = m_Entities.find(a_MeshRenderer)->second;
				SafeDelete(temp);
				m_Entities.erase(a_MeshRenderer);
			}
		}

		void GLRenderer::SetCamera(Scene::CCamera *a_Camera)
		{
			Camera = a_Camera;
		}

		Scene::CCamera *GLRenderer::GetCamera()
		{
			return Camera;
		}

		void GLRenderer::Shutdown()
		{
			for (auto &temp : m_Entities)
			{
				SafeDelete(temp.second);
			}
			m_Entities.clear();

			SafeDelete(m_Container);

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