#include "Dome.h"
#include "BasicLogger.h"
#include "CullMode.h"
using namespace DirectX::SimpleMath;

Dome::Dome(void)
	: GameObject()
{

}

Dome::Dome(Vector3& const position, Vector3& const rotation, Vector3& const scale)
	: GameObject(position, rotation, scale)
{

}

Dome::~Dome(void)
{

}

void Dome::Initialize(GraphicsManager* const gm)
{
	//m_platform = DirectX::GeometricPrimitive::CreateHemisphere(gm->GetDeviceContext(), 1.0f, 16, true);
	m_dome = DirectX::GeometricPrimitive::CreateHemisphere(gm->GetDeviceContext(), 1.0f, 16, false);
}

void Dome::Destroy(void)
{

}

//void Dome::Update(TimeManager* time)
//{
//
//}

void Dome::Render(const Matrix& projection, const Matrix& view, bool const wireFrame)
{
	Vector3 const transfRotation = GetTransform()->GetRotation();

	Vector4 const rotationMatrix = DirectX::XMQuaternionRotationRollPitchYaw(transfRotation.x, transfRotation.y, transfRotation.z);
	Matrix const local = DirectX::XMMatrixMultiply(Matrix::Identity, XMMatrixTransformation(Vector4::Zero, Quaternion::Identity, GetTransform()->GetScale(), Vector4::Zero, rotationMatrix, GetTransform()->GetPosition()));

	Vector4 const color = Vector4(1.0f, 1.0f, 1.0f, .5f);
	m_dome->Draw(local, view, projection, color, nullptr, wireFrame, nullptr);
}