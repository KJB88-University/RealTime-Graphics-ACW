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
	m_body.reset(DirectX::Model::CreateFromSDKMESH(gfx->GetDevice(), L"DFbody.sdkmesh", *gfx->GetFXFactory()).release());

	m_wings = new DragonflyWings(L"DFleftwing.sdkmesh", L"DFrightwing.sdkmesh"); // TODO - set position
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
	m_legs->Update(time, m_transform);
	m_wings->Update(time, m_transform);
}

void Dragonfly::Render(GraphicsManager* gfx, Matrix proj, Matrix view, bool wireFrame)
{
	m_legs->Render(gfx, Matrix::Identity, proj, view, wireFrame);
	m_wings->Render(gfx, Matrix::Identity, proj, view, wireFrame);

	Vector4 qid = DirectX::XMQuaternionIdentity();
	Vector4 rotationMatrix = DirectX::XMQuaternionRotationRollPitchYaw(m_transform->GetRotation().x, m_transform->GetRotation().y, m_transform->GetRotation().z);

	Matrix world = Matrix::Identity;

	Matrix local = DirectX::XMMatrixMultiply
	(
		world,
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


	// Draw the model
	m_body->Draw(gfx->GetDeviceContext(), *gfx->GetCommonStates(), local, view, proj, wireFrame, [&]
	{
		gfx->GetCommonStates()->Opaque();
		gfx->GetCommonStates()->DepthDefault();
	}
	);


}
