#include "Platform.h"

#include "DDSTextureLoader.h"
//#include "BasicLogger.h" // debug, not needed for submission

using namespace DirectX::SimpleMath;

Platform::Platform(void)
	: GameObject(), m_texture(nullptr)
{

}

Platform::Platform(Vector3& const position, Vector3& const rotation, Vector3& const scale)
	: GameObject(position, rotation, scale), m_texture(nullptr)
{

}

Platform::~Platform(void)
{

}

void Platform::Initialize(GraphicsManager* const gm)
{
	HRESULT hr;

	//m_platform = DirectX::GeometricPrimitive::CreateHemisphere(gm->GetDeviceContext(), 1.0f, 16, true);
	m_platform = DirectX::GeometricPrimitive::CreateCylinder(gm->GetDeviceContext(), 0.1f, 1.0f, 64, true);

	hr = DirectX::CreateDDSTextureFromFile(gm->GetDevice(), L"seafloor.dds", nullptr, &m_texture);
//#if _DEBUG
//	if (FAILED(hr))
//	{
//		BasicLogger::WriteToConsole("PLATFORM: Unable to load texture file.\n");
//	}
//#endif
}

void Platform::Destroy(void)
{

}

//void Platform::Update(TimeManager* time)
//{
//
//}

void Platform::Render(const Matrix& projection, const Matrix& view, bool const wireFrame)
{
	Vector3 const transfRotation = GetTransform()->GetRotation();

	Vector4 const rotationMatrix = DirectX::XMQuaternionRotationRollPitchYaw(transfRotation.x, transfRotation.y, transfRotation.z);
	Matrix const local = DirectX::XMMatrixMultiply(Matrix::Identity, XMMatrixTransformation(Vector4::Zero, Quaternion::Identity, GetTransform()->GetScale(), Vector4::Zero, rotationMatrix, GetTransform()->GetPosition()));

	m_platform->Draw(local, view, projection, Vector4(1.0f, 1.0f, 1.0f, 1.0f), m_texture, wireFrame, nullptr);
}