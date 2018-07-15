#include "Tiny.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Tiny::Tiny(void)
	: m_position(0.0f, 0.0f, 0.0f), m_rotation(0.0f, 0.0f, 0.0f), m_scale(1.0f, 1.0f, 1.0f)
{

}

Tiny::~Tiny(void)
{

}

void Tiny::Initialize(ID3D11Device* device, const wchar_t* fileName, IEffectFactory& fxFactory)
{
	// Assign the Model to a class member unique_ptr
	m_tiny.reset(DirectX::Model::CreateFromSDKMESH(device, fileName, fxFactory).release());
}

void Tiny::Update(void)
{

}

void Tiny::Render(ID3D11DeviceContext* context, DirectX::CommonStates* m_states)
{
	// DEBUG
	Vector3 eye = { 0.0f, 0.0f, 0.0f };
	Vector3 lookat = { 0.0f, 0.0f, -1.0f };
	Matrix g_View = Matrix::CreateLookAt(eye, lookat, Vector3::UnitY);

	
	float nearClip = 0.01f;
	float farClip = 1000.0f;
	float aspectRatio = 800 / 600.0f;
	float FoV = XM_PIDIV4;
	Matrix g_Projection = Matrix::CreatePerspectiveFieldOfView(FoV, aspectRatio, nearClip, farClip);

	Matrix g_World = Matrix::Identity;
	Vector4 qid = XMQuaternionIdentity();
	const Vector3 scale = { 0.01f, 0.01f, 0.01f };
	const Vector3 translate = { 0.0f, 0.0f, -10.0f };
	Vector4 rotate = DirectX::XMQuaternionRotationRollPitchYaw(-1.7f, 0.0f, 0.0f);
	Matrix local = DirectX::XMMatrixMultiply(g_World, XMMatrixTransformation(g_XMZero, qid, scale, g_XMZero, rotate, translate));

	// END DEBUG

	// Draw the model
	m_tiny->Draw(context, g_States, local, g_View, g_Projection);
}