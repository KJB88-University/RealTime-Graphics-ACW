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

	m_frontLegs.reset(DirectX::Model::CreateFromSDKMESH(gfx->GetDevice(), L"DFfrontlegs.sdkmesh", *gfx->GetFXFactory()).release());
	m_midLegs.reset(DirectX::Model::CreateFromSDKMESH(gfx->GetDevice(), L"DFmiddlelegs.sdkmesh", *gfx->GetFXFactory()).release());
	m_backLegs.reset(DirectX::Model::CreateFromSDKMESH(gfx->GetDevice(), L"DFbacklegs.sdkmesh", *gfx->GetFXFactory()).release());

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
	//m_transform->SetRotation(0.0f, 1.0f, 0.0f);
}

void Dragonfly::Render(GraphicsManager* gfx, TimeManager* time, Matrix world, Matrix proj, Matrix view, bool wireFrame)
{
	world = Matrix::CreateTranslation(m_transform->GetPosition());

	// Draw body
	m_body->Draw(gfx->GetDeviceContext(), *gfx->GetCommonStates(), world, view, proj, wireFrame, nullptr);

	// Draw legs
	world = Matrix::CreateTranslation
	(
		Vector3
		(
			m_transform->GetPosition().x,
			m_transform->GetPosition().y - 0.25f,
			m_transform->GetPosition().z + 0.75f
		)
	);

	m_frontLegs->Draw(gfx->GetDeviceContext(), *gfx->GetCommonStates(), world, view, proj, wireFrame, nullptr);
	m_midLegs->Draw(gfx->GetDeviceContext(), *gfx->GetCommonStates(), world, view, proj, wireFrame, nullptr);
	m_backLegs->Draw(gfx->GetDeviceContext(), *gfx->GetCommonStates(), world, view, proj, wireFrame, nullptr);

	// Wrap in animation conditional
	Matrix worldLeft;

	// Draw left wing
	float t = time->GetTotalElapsedTime();
	worldLeft = Matrix::CreateRotationZ(sin(t)) * Matrix::CreateTranslation(m_transform->GetPosition());
	m_leftWing->Draw(gfx->GetDeviceContext(), *gfx->GetCommonStates(), worldLeft, view, proj, wireFrame, nullptr);

	// Draw right wing
	Matrix worldRight;
	worldRight = Matrix::CreateRotationZ(-sin(t)) * Matrix::CreateTranslation(m_transform->GetPosition());
	m_rightWing->Draw(gfx->GetDeviceContext(), *gfx->GetCommonStates(), worldRight, view, proj, wireFrame, nullptr);
}
