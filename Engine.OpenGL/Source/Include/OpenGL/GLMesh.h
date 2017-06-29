#pragma once

#include <GLEW\Include\glew.h>
#include "Graphics\Interfaces\IMesh.h"

#include <unordered_set>

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

			std::unordered_set<Matrix4f*> m_Transforms;

			unsigned int m_VertexCount = 0;
			unsigned int m_InstanceCount = 0;
			unsigned int m_FrustumInstanceCount = 0;

		public:
			bool ShouldCull = true;
			bool HasIndices = true;
			EMeshPrimitive Mode;

			~GLMesh();

			bool Initialize(SMeshDesc &a_Desc, IRenderer *a_Renderer) final;

			void AddInstance(Matrix4f *a_MeshRenderer) final;
			void RemoveInstance(Matrix4f *a_MeshRenderer) final;

			void Bind() final;
			void Unbind() final;

			GLuint GetVertexCount() final { return m_VertexCount; };
			unsigned int GetInstanceCount() final { return m_InstanceCount; };
			unsigned int GetFrustumInstanceCount() final { return m_FrustumInstanceCount; };
		};
	}
}