#pragma once

#include "Graphics\Descriptions\SEntityDesc.h"

namespace Scene
{
	class CMeshRenderer;
}

namespace Graphics
{
	class IRenderer;

	class IEntity
	{
	public:
		
		virtual ~IEntity() { }
		
		virtual	bool Initialize(SEntityDesc &a_Desc, IRenderer *a_Renderer) = 0;

		virtual void Render() = 0;

		virtual void AddInstance(Scene::CMeshRenderer *a_MeshRenderer) = 0;
		virtual void RemoveInstance(Scene::CMeshRenderer *a_MeshRenderer) = 0;

		virtual size_t GetInstanceCount() = 0;

		//virtual void SetBuffer() = 0;
	};
}