#include "Platform.h"

#include "DDSTextureLoader.h"
#include "BasicLogger.h"
using namespace DirectX::SimpleMath;

Platform::Platform(void)
	: m_position(0.0f, 0.0f, -10.0f), m_rotation(0.0f, 0.0f, 0.0f), m_scale(1.0f, 1.0f, 1.0f)
{

}

Platform::~Platform(void)
{

}

void Platform::Initialize(GraphicsManager* gm)
{
	HRESULT hr;

	m_platform = DirectX::GeometricPrimitive::CreateCylinder(gm->GetDeviceContext(), 0.1f, 1.0f, 16, false);

	hr = DirectX::CreateDDSTextureFromFile(gm->GetDevice(), L"seafloor.dds", nullptr, &m_texture);
	if (FAILED(hr))
	{
		BasicLogger::WriteToConsole("PLATFORM: Unable to load texture file.\n");
	}
}

void Platform::Destroy(void)
{

}

void Platform::Update(void)
{

}

void Platform::Render(GraphicsManager* gm, Matrix projection, Matrix view)
{
	Vector4 rotationMatrix = DirectX::XMQuaternionRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);
	Matrix local = DirectX::XMMatrixMultiply(Matrix::Identity, XMMatrixTransformation(Vector4::Zero, Quaternion::Identity, m_scale, Vector4::Zero, rotationMatrix, m_position));
	m_platform->Draw(local, view, projection, Vector4(1.0f, 1.0f, 1.0f, 1.0f), m_texture);
}