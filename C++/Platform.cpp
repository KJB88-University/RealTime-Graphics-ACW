#include "Platform.h"

#include "DDSTextureLoader.h"
#include "BasicLogger.h"

using namespace DirectX::SimpleMath;

Platform::Platform(void)
	: GameObject()
{

}

Platform::Platform(Vector3 position, Vector3 rotation, Vector3 scale)
	: GameObject(position, rotation, scale)
{

}

Platform::~Platform(void)
{

}

void Platform::Initialize(GraphicsManager* gm)
{
	HRESULT hr;

	//m_platform = DirectX::GeometricPrimitive::CreateHemisphere(gm->GetDeviceContext(), 1.0f, 16, true);
	m_platform = DirectX::GeometricPrimitive::CreateCylinder(gm->GetDeviceContext(), 0.1f, 1.0f, 16, true);

	hr = DirectX::CreateDDSTextureFromFile(gm->GetDevice(), L"seafloor.dds", nullptr, &m_texture);
	if (FAILED(hr))
	{
		BasicLogger::WriteToConsole("PLATFORM: Unable to load texture file.\n");
	}
}

void Platform::Destroy(void)
{

}

void Platform::Update(TimeManager* time)
{

}

void Platform::Render(GraphicsManager* gm, Matrix projection, Matrix view)
{
	Vector3 transfRotation = m_transform->GetRotation();

	Vector4 rotationMatrix = DirectX::XMQuaternionRotationRollPitchYaw(transfRotation.x, transfRotation.y, transfRotation.z);
	Matrix local = DirectX::XMMatrixMultiply(Matrix::Identity, XMMatrixTransformation(Vector4::Zero, Quaternion::Identity, m_transform->GetScale(), Vector4::Zero, rotationMatrix, m_transform->GetPosition()));

	m_platform->Draw(local, view, projection, Vector4(1.0f, 1.0f, 1.0f, 1.0f), m_texture);
}