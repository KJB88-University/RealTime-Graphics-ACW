#include "Tiny.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Tiny::Tiny(void)
	: GameObject(Vector3(0.0f, 0.0f, -10.0f), Vector3(-1.7f, 0.0f, 0.0f), Vector3(0.01f, 0.01f, 0.01f))
{

}

Tiny::~Tiny(void)
{

}

void Tiny::Initialize(GraphicsManager* gfx, const wchar_t* fileName)
{
	// Assign the Model to a class member unique_ptr
	m_tiny.reset(DirectX::Model::CreateFromSDKMESH(gfx->GetDevice(), fileName, *gfx->GetFXFactory()).release());
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
	// DEBUG
	/*
	Vector3 eye = { 0.0f, 0.0f, 0.0f };
	Vector3 lookat = { 0.0f, 0.0f, -1.0f };
	Matrix g_View = Matrix::CreateLookAt(eye, lookat, Vector3::UnitY);

	float nearClip = 0.01f;
	float farClip = 1000.0f;
	float aspectRatio = 800 / 600.0f;
	float FoV = XM_PIDIV4;
	Matrix g_Projection = Matrix::CreatePerspectiveFieldOfView(FoV, aspectRatio, nearClip, farClip);
	*/

	Vector4 qid = XMQuaternionIdentity();
	//const Vector3 scale = { 0.01f, 0.01f, 0.01f };
	//const Vector3 translate = { 0.0f, 0.0f, -10.0f };
	Vector4 rotationMatrix = DirectX::XMQuaternionRotationRollPitchYaw(m_transform->GetRotation().x, m_transform->GetRotation().y, m_transform->GetRotation().z);

	
	Matrix g_World;
	/*
	static uint64_t dwTimeStart = 0;
	static uint64_t dwTimeLast = 0;
	uint64_t dwTimeCur = GetTickCount64();
	if (dwTimeStart == 0)
		dwTimeStart = dwTimeCur;
	float t = (dwTimeCur - dwTimeStart) / 1000.0f;
	float dt = (dwTimeCur - dwTimeLast) / 1000.0f;
	dwTimeLast = dwTimeCur;

	g_World = Matrix::CreateRotationZ(t);
	*/

	Matrix local = DirectX::XMMatrixMultiply(g_World, XMMatrixTransformation(Vector4::Zero, Quaternion::Identity, m_transform->GetScale(), Vector4::Zero, rotationMatrix, m_transform->GetPosition()));

	// END DEBUG

	// Draw the model
	if (!wireFrame)
	{
		m_tiny->Draw(gfx->GetDeviceContext(), *gfx->GetCommonStates(), local, view, projection);
	}
	else
	{
		m_tiny->Draw(gfx->GetDeviceContext(), *gfx->GetCommonStates(), local, view, projection, true, nullptr);
	}
}