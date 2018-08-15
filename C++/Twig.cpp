#include "Twig.h"
#include <DDSTextureLoader.h>
using namespace DirectX::SimpleMath;

Twig::Twig(void)
	: GameObject()
{

}

Twig::Twig(Vector3& const position, Vector3& const rotation, Vector3& const scale)
	: GameObject(position, rotation, scale)
{

}

Twig::~Twig(void)
{

}

void Twig::Initialize(GraphicsManager* const gfx)
{
	m_twig = DirectX::GeometricPrimitive::CreateCylinder(gfx->GetDeviceContext(), 1.0f, 1.0f, 16, true);
	GetTransform()->SetRotation(DirectX::XM_PIDIV2, 0.0f, 0.0f);
}

void Twig::Destroy(void)
{
	m_twig.release();
	m_twig = nullptr;
}

//void Twig::Update(TimeManager* time)
//{
//
//}

void Twig::Render(const Matrix& proj, const Matrix& view, bool const wireFrame)
{
	Vector3 const transfRotation = GetTransform()->GetRotation();

	Vector4 const rotationMatrix = DirectX::XMQuaternionRotationRollPitchYaw(transfRotation.x, transfRotation.y, transfRotation.z);
	Matrix const local = DirectX::XMMatrixMultiply(Matrix::Identity, XMMatrixTransformation(Vector4::Zero, Quaternion::Identity, GetTransform()->GetScale(), Vector4::Zero, rotationMatrix, GetTransform()->GetPosition()));
	
	m_twig->Draw(local, view, proj, Vector4(0.35f, 0.25f, 0.125f, 1.0f), nullptr, wireFrame, nullptr);
}

