#pragma once

#include "Graphics\Descriptions\SMeshDesc.h"

#include "Scene\GameObject\GameObject.h"
#include "Scene\GameObject\Components\CMeshRenderer.h"
#include "Scene\GameObject\Components\Transformation.h"

namespace Graphics
{
	class IRenderer;

	class IMesh
	{
	public:
		virtual ~IMesh() { }

		virtual bool Initialize(SMeshDesc &a_Desc, IRenderer *a_Renderer) = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		// Methods for instanced rendering
		//
		virtual void AddInstance(Scene::CMeshRenderer *a_MeshRenderer) = 0;
		virtual void RemoveInstance(Scene::CMeshRenderer *a_MeshRenderer) = 0;

		virtual unsigned int GetVertexCount() = 0;
		virtual unsigned int GetInstanceCount() = 0;
		virtual unsigned int GetFrustumInstanceCount() = 0;
	};
}