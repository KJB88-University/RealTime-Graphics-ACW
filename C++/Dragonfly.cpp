#include "Dragonfly.h"
using namespace DirectX::SimpleMath;

Dragonfly::Dragonfly(void)
	: GameObject()
{

}

Dragonfly::Dragonfly(Vector3 position, Vector3 rotation, Vector3 scale)
	: GameObject(position, rotation, scale)
{

}

Dragonfly::Dragonfly(const Dragonfly& other)
{

}

Dragonfly::~Dragonfly(void)
{

}

void Dragonfly::Initialize(GraphicsManager* gfx)
{
	// Assign the Model to a class member unique_ptr
	m_body.reset(DirectX::Model::CreateFromSDKMESH(gfx->GetDevice(), L"", *gfx->GetFXFactory()).release());

	m_wings = new DragonflyWing(); // TODO - set position
	m_wings->Initialize(gfx);

	m_legs = new DragonflyLegs(); // TODO - Set position
	m_legs->Initialize(gfx);


}

void Dragonfly::Destroy(void)
{
	m_body.release();
	m_body = nullptr;

	m_legs->Destroy();
	delete m_legs;
	m_legs = nullptr;

	m_wings->Destroy();
	delete m_wings;
	m_wings = nullptr;
}

void Dragonfly::Update(TimeManager* time)
{

}

void Dragonfly::Render(GraphicsManager* gfx, Matrix* world, Matrix* proj, Matrix* view, bool wireFrame)
{
	Vector4 qid = DirectX::XMQuaternionIdentity();
	Vector4 rotationMatrix = DirectX::XMQuaternionRotationRollPitchYaw(m_transform->GetRotation().x, m_transform->GetRotation().y, m_transform->GetRotation().z);

	Matrix local = DirectX::XMMatrixMultiply
	(
		*world,
		XMMatrixTransformation
		(
			Vector4::Zero,
			Quaternion::Identity, 
			m_transform->GetScale(),
			Vector4::Zero,
			rotationMatrix,
			m_transform->GetPosition()
		)
	);

	// END DEBUG

	// Draw the model
	m_body->Draw(gfx->GetDeviceContext(), *gfx->GetCommonStates(), local, *view, *proj, wireFrame, nullptr);
}
