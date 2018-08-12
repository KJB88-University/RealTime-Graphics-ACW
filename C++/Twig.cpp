#include "Twig.h"

using namespace DirectX::SimpleMath;

Twig::Twig(void)
	: GameObject()
{

}

Twig::Twig(Vector3 position, Vector3 rotation, Vector3 scale)
	: GameObject(position, rotation, scale)
{

}

Twig::Twig(const Twig& other)
	: GameObject()
{

}

Twig::~Twig(void)
{

}

void Twig::Initialize(GraphicsManager* gfx)
{
	m_twig = DirectX::GeometricPrimitive::CreateCylinder(gfx->GetDeviceContext(), 1.0f, 1.0f, 16, true);
	m_transform->SetRotation(DirectX::XM_PIDIV2, 0.0f, 0.0f);
}

void Twig::Destroy(void)
{
	m_twig.release();
	m_twig = nullptr;
}

void Twig::Update(TimeManager* time)
{

}

void Twig::Render(GraphicsManager* gfx, Matrix proj, Matrix view,  bool wireFrame)
{
	Vector3 transfRotation = m_transform->GetRotation();

	Vector4 rotationMatrix = DirectX::XMQuaternionRotationRollPitchYaw(transfRotation.x, transfRotation.y, transfRotation.z);
	Matrix local = DirectX::XMMatrixMultiply(Matrix::Identity, XMMatrixTransformation(Vector4::Zero, Quaternion::Identity, m_transform->GetScale(), Vector4::Zero, rotationMatrix, m_transform->GetPosition()));
	
	m_twig->Draw(local, view, proj, Vector4(0.35f, 0.25f, 0.125f, 1.0f), nullptr, wireFrame, nullptr);
}

