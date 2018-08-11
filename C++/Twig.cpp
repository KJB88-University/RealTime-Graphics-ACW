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
	m_twig = DirectX::GeometricPrimitive::CreateCylinder(gfx->GetDeviceContext(), 1.0f, 1.0f, 16, false);
	m_transform->SetRotation(90.0f, 0.0f, 0.0f);
}

void Twig::Destroy(void)
{

}

void Twig::Update(TimeManager* time)
{

}

void Twig::Render(GraphicsManager* gfx, Matrix view, Matrix proj, bool wireFrame)
{
	Vector3 transfRotation = m_transform->GetRotation();

	Vector4 rotationMatrix = DirectX::XMQuaternionRotationRollPitchYaw(transfRotation.x, transfRotation.y, transfRotation.z);
	Matrix local = DirectX::XMMatrixMultiply(Matrix::Identity, XMMatrixTransformation(Vector4::Zero, Quaternion::Identity, m_transform->GetScale(), Vector4::Zero, rotationMatrix, m_transform->GetPosition()));

	m_twig->Draw(local, view, proj, Vector4(.5f, 0.25f, 0.1f, 1.0f), nullptr, wireFrame, nullptr);
}

