#include "Scene\GameObject\Components\CRigidbody.h"

#include "Utilities\Event\EventHandler.h"
#include "Utilities\Event\SEventDesc.h"

#include "Scene\GameObject\GameObject.h"
#include "Scene\GameObject\Components\Transformation.h"

#include "Math\Math.h"

namespace Scene
{
	CRigidbody::~CRigidbody()
	{
		Core::SEventDesc eventDesc{};

		eventDesc.Description = this;
		eventDesc.Event = Core::EEvents::SCENE_RIGIDBODY_REMOVED;

		Core::EventHandler::StaticClass()->ForceEvent(eventDesc);
	}

	bool CRigidbody::Initialize()
	{
		btQuaternion rotation;

		float t0 = std::cos((Parent->Transform->Position.z * DEGTORAD) * 0.5f);
		float t1 = std::sin((Parent->Transform->Position.z * DEGTORAD) * 0.5f);
		float t2 = std::cos((Parent->Transform->Position.x * DEGTORAD) * 0.5f);
		float t3 = std::sin((Parent->Transform->Position.x * DEGTORAD) * 0.5f);
		float t4 = std::cos((Parent->Transform->Position.y * DEGTORAD) * 0.5f);
		float t5 = std::sin((Parent->Transform->Position.y * DEGTORAD) * 0.5f);
		
		rotation.setW(t0 * t2 * t4 + t1 * t3 * t5);
		rotation.setX(t0 * t3 * t4 - t1 * t2 * t5);
		rotation.setY(t0 * t2 * t5 + t1 * t3 * t4);
		rotation.setZ(t1 * t2 * t4 - t0 * t3 * t5);

		printf("%f %f %f %f\n", rotation.getX(), rotation.getY(), rotation.getZ(), rotation.getW());

		m_MotionState =
			std::make_unique<btDefaultMotionState>
			(btTransform(btQuaternion(0.707f, 0.0f, 0.0f, 0.707f),
			btVector3(Parent->Transform->Position.x, Parent->Transform->Position.y, Parent->Transform->Position.z)));

		m_CollisionShape = std::make_unique<btSphereShape>(1.0f);

		btVector3 fallInertia(0, 0, 0);
		m_CollisionShape->calculateLocalInertia(1.0f, fallInertia);

		btRigidBody::btRigidBodyConstructionInfo
			groundRigidBodyCI(1.0f,
				m_MotionState.get(), m_CollisionShape.get(), fallInertia);
		
		m_Body = std::make_unique<btRigidBody>(groundRigidBodyCI);

		//m_Body->applyTorque(btVector3(20, 0, 20));
		m_Body->applyForce(btVector3(0, 5000, 0), btVector3(0,0,0));

		//

		Core::SEventDesc eventDesc{};
		
		eventDesc.Description = this;
		eventDesc.Event = Core::EEvents::SCENE_RIGIDBODY_ADDED;

		Core::EventHandler::StaticClass()->AddEvent(eventDesc);

		return true;
	}

	void CRigidbody::Update()
	{
		
		btTransform trans;
		m_Body->getMotionState()->getWorldTransform(trans);
		
		btQuaternion q = trans.getRotation();

		float ysqr = q.y() * q.y();

		// roll (x-axis rotation)
		float t0 = 2.0f * (q.w() * q.x() + q.y() * q.z());
		float t1 = 1.0f - 2.0f * (q.x() * q.x() + ysqr);
		float roll = std::atan2(t0, t1);

		// pitch (y-axis rotation)
		float t2 = 2.0f * (q.w() * q.y() - q.z() * q.x());
		t2 = ((t2 > 1.0f) ? 1.0f : t2);
		t2 = ((t2 < -1.0f) ? -1.0f : t2);
		float pitch = std::asin(t2);

		// yaw (z-axis rotation)
		float t3 = 2.0f * (q.w() * q.z() + q.x() * q.y());
		float t4 = 1.0f - 2.0f * (ysqr + q.z() * q.z());
		float yaw = std::atan2(t3, t4);

		Parent->Transform->Position = Vector3f(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
		Parent->Transform->Rotation = Vector3f(roll * RADTODEG, pitch * RADTODEG, yaw * RADTODEG);
	}
}