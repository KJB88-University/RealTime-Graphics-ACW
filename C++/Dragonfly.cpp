#include "Dragonfly.h"
using namespace DirectX::SimpleMath;

Dragonfly::Dragonfly(void)
	: GameObject()
{

}

Dragonfly::Dragonfly(Vector3 position, Vector3 rotation, Vector3 scale)
	: GameObject(position, rotation, scale)
{

}

Dragonfly::Dragonfly(const Dragonfly& other)
{

}

Dragonfly::~Dragonfly(void)
{

}

void Dragonfly::Initialize(GraphicsManager* gfx)
{
	// Assign the Model to a class member unique_ptr
	m_body.reset(DirectX::Model::CreateFromSDKMESH(gfx->GetDevice(), L"DFbody.sdkmesh", *gfx->GetFXFactory()).release());
	//m_body.reset(DirectX::Model::CreateFromSDKMESH(gfx->GetDevice(), L"Dragonfly.sdkmesh", *gfx->GetFXFactory()).release());

	m_legs.reset(DirectX::Model::CreateFromSDKMESH(gfx->GetDevice(), L"DFlegs.sdkmesh", *gfx->GetFXFactory()).release());

	m_leftWing.reset(DirectX::Model::CreateFromSDKMESH(gfx->GetDevice(), L"DFdoubleFixedLeft.sdkmesh", *gfx->GetFXFactory()).release());
	m_rightWing.reset(DirectX::Model::CreateFromSDKMESH(gfx->GetDevice(), L"DFdoubleFixedRight.sdkmesh", *gfx->GetFXFactory()).release());
}

void Dragonfly::Destroy(void)
{
	m_body.release();
	m_body = nullptr;

}

void Dragonfly::Update(TimeManager* time)
{
	//m_world *= Matrix::CreateRotationZ(time->GetDeltaTime() * 2.0f);
}

void Dragonfly::Render(GraphicsManager* gfx, Matrix proj, Matrix view, bool wireFrame)
{
	m_world = Matrix::CreateTranslation(m_transform->GetPosition());

	// Draw the model
	m_body->Draw(gfx->GetDeviceContext(), *gfx->GetCommonStates(), m_world, view, proj, wireFrame, nullptr);
	m_legs->Draw(gfx->GetDeviceContext(), *gfx->GetCommonStates(), m_world, view, proj, wireFrame, nullptr);

	m_world = Matrix::CreateTranslation(m_transform->GetPosition() * 1.25f);
	m_leftWing->Draw(gfx->GetDeviceContext(), *gfx->GetCommonStates(), m_world, view, proj, wireFrame, nullptr);
	m_rightWing->Draw(gfx->GetDeviceContext(), *gfx->GetCommonStates(), m_world, view, proj, wireFrame, nullptr);
}
