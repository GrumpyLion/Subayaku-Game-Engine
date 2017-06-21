#pragma once

#include <GLEW\Include\glew.h>
#include "Graphics\Interfaces\IMesh.h"

#include <unordered_set>

namespace Scene
{
	class CMeshRenderer;
}

namespace Graphics
{
	namespace OpenGL
	{
		const int numVBOs = 6;

		class GLMesh : public IMesh
		{
		private:
			GLuint m_VAO = 0;
			GLuint m_VBOs[numVBOs];
			GLuint m_TBO = 0;
			GLuint m_Count = 0;

			std::unordered_set<Scene::CMeshRenderer*> m_Transforms;
			unsigned int m_OldSize = 0;

		public:
			bool ShouldCull = true;
			bool HasIndices = true;
			EMeshPrimitive Mode;

			~GLMesh();
			bool Initialize(SMeshDesc &a_Desc, IRenderer *a_Renderer) final;
			void AddInstance(Scene::CMeshRenderer *a_MeshRenderer);
			void RemoveInstance(Scene::CMeshRenderer *a_MeshRenderer);

			void Bind() final;
			void Unbind() final;
			GLuint GetCount() final;
			size_t GetInstanceCount();
		};
	}
}