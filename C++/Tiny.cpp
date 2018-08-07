#include "Tiny.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Tiny::Tiny(void)
	: GameObject(Vector3(0.0f, 0.0f, -10.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f))
{

}

Tiny::~Tiny(void)
{

}

void Tiny::Initialize(GraphicsManager* gfx)
{
	// Assign the Model to a class member unique_ptr
	m_tiny.reset(DirectX::Model::CreateFromSDKMESH(gfx->GetDevice(), L"tiny.sdkmesh", *gfx->GetFXFactory()).release());
}

void Tiny::Destroy(void)
{
	m_tiny.release();
	m_tiny = nullptr;
}

void Tiny::Update(TimeManager* time)
{
	// STUB
}

void Tiny::Render(GraphicsManager* gfx, Matrix projection, Matrix view, bool wireFrame)
{
	Vector4 qid = XMQuaternionIdentity();
	Vector4 rotationMatrix = DirectX::XMQuaternionRotationRollPitchYaw(m_transform->GetRotation().x, m_transform->GetRotation().y, m_transform->GetRotation().z);
	Matrix g_World;

	Matrix local = DirectX::XMMatrixMultiply
	(
		g_World,
		XMMatrixTransformation
		(
			Vector4::Zero,
			Quaternion::Identity, m_transform->GetScale(),
			Vector4::Zero,
			rotationMatrix,
			m_transform->GetPosition()
		)
	);

	// END DEBUG

	// Draw the model
	m_tiny->Draw(gfx->GetDeviceContext(), *gfx->GetCommonStates(), local, view, projection, wireFrame, nullptr);
}