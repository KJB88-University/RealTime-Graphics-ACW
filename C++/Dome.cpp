#include "Dome.h"
#include "BasicLogger.h"

using namespace DirectX::SimpleMath;

Dome::Dome(void)
	: GameObject()
{

}

Dome::Dome(Vector3 position, Vector3 rotation, Vector3 scale)
	: GameObject(position, rotation, scale)
{

}

Dome::~Dome(void)
{

}

void Dome::Initialize(GraphicsManager* gm)
{
	HRESULT hr;

	//m_platform = DirectX::GeometricPrimitive::CreateHemisphere(gm->GetDeviceContext(), 1.0f, 16, true);
	m_dome = DirectX::GeometricPrimitive::CreateHemisphere(gm->GetDeviceContext(), 1.0f, 16, false);

	//hr = DirectX::CreateDDSTextureFromFile(gm->GetDevice(), L"seafloor.dds", nullptr, &m_texture);
	//if (FAILED(hr))
	//{
	//	BasicLogger::WriteToConsole("PLATFORM: Unable to load texture file.\n");
	//}
}

void Dome::Destroy(void)
{

}

void Dome::Update(TimeManager* time)
{

}

void Dome::Render(GraphicsManager* gm, DirectX::SimpleMath::Matrix projection, DirectX::SimpleMath::Matrix view, bool wireFrame)
{
	Vector3 transfRotation = m_transform->GetRotation();

	Vector4 rotationMatrix = DirectX::XMQuaternionRotationRollPitchYaw(transfRotation.x, transfRotation.y, transfRotation.z);
	Matrix local = DirectX::XMMatrixMultiply(Matrix::Identity, XMMatrixTransformation(Vector4::Zero, Quaternion::Identity, m_transform->GetScale(), Vector4::Zero, rotationMatrix, m_transform->GetPosition()));

	
	m_dome->Draw(local, view, projection, Vector4(1.0f, 1.0f, 1.0f, 1.0f), nullptr, wireFrame, nullptr);
}