#pragma once

#include "Interface\IComponent.h"

#include <Bullet\btBulletDynamicsCommon.h>
#include <memory>

namespace Scene
{
	class CRigidbody : public IComponent
	{
	private:
		std::unique_ptr<btRigidBody> m_Body;
		std::unique_ptr<btMotionState> m_MotionState;
		std::unique_ptr<btCollisionShape> m_CollisionShape;

	public:	
		
		~CRigidbody();

		CRigidbody(GameObject *a_Parent)
			: IComponent(a_Parent) {	}

		bool Initialize();
		
		void Update();

		btRigidBody *GetRigidbody() { return m_Body.get(); };
	};
}