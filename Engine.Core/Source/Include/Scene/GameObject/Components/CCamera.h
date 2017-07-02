#pragma once

#include "Interface\IComponent.h"
#include "Math\Math.h"
#include "Graphics\Camera.h"

#include <memory>

namespace Scene
{
	class CCamera : public IComponent
	{
	private:
		std::unique_ptr<Graphics::Camera> m_Camera;
	
	public:
		~CCamera();

		bool CurrentCamera = false;
		
		CCamera(GameObject *a_Parent);

		bool Initialize(float a_FOV, float a_Near, float a_Far);
		void Update() override;

		Graphics::Camera *GetCamera() { return m_Camera.get(); };
	};
}