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
	: GameObject()
{

}

Dragonfly::~Dragonfly(void)
{

}

void Dragonfly::Initialize(GraphicsManager* gfx)
{
	// Assign the Model to a class member unique_ptr
	m_body.reset(DirectX::Model::CreateFromSDKMESH(gfx->GetDevice(), L"DFbody.sdkmesh", *gfx->GetFXFactory()).release());

	// Legs
	m_frontLegs.reset(DirectX::Model::CreateFromSDKMESH(gfx->GetDevice(), L"DFfrontlegs.sdkmesh", *gfx->GetFXFactory()).release());
	m_midLegs.reset(DirectX::Model::CreateFromSDKMESH(gfx->GetDevice(), L"DFmiddlelegs.sdkmesh", *gfx->GetFXFactory()).release());
	m_backLegs.reset(DirectX::Model::CreateFromSDKMESH(gfx->GetDevice(), L"DFbacklegs.sdkmesh", *gfx->GetFXFactory()).release());

	// Wings
	m_leftWing.reset(DirectX::Model::CreateFromSDKMESH(gfx->GetDevice(), L"DFdoubleFixedLeft.sdkmesh", *gfx->GetFXFactory()).release());
	m_rightWing.reset(DirectX::Model::CreateFromSDKMESH(gfx->GetDevice(), L"DFdoubleFixedRight.sdkmesh", *gfx->GetFXFactory()).release());

	Vector3 pos = m_transform->GetPosition();
	Vector3 defaultPos = m_transform->GetDefaultPosition();
}

void Dragonfly::Destroy(void)
{
	// Release models
	m_body.release();
	m_body = nullptr;

	m_frontLegs.release();
	m_frontLegs = nullptr;

	m_midLegs.release();
	m_midLegs = nullptr;

	m_backLegs.release();
	m_backLegs = nullptr;

	m_leftWing.release();
	m_leftWing = nullptr;

	m_rightWing.release();
	m_rightWing = nullptr;

}

void Dragonfly::Update(TimeManager* time)
{
	if (playAnimation)
	{
		if (m_transform->GetPosition().y >= 10.0f)
		{
			upperLimit = true;
		}
		else if (m_transform->GetPosition().y < 2.25f)
		{
			playAnimation = false;
			upperLimit = false;
		}
		// Flying up
		if (!upperLimit)
		{
			Vector3 pos = m_transform->GetPosition();
			pos += Vector3(0.0f, 1.0f * time->GetDeltaTime(), 0.0f);
			m_transform->SetPosition(pos);
		}
		
		// Flying down
		else
		{
			Vector3 pos = m_transform->GetPosition();
			pos += Vector3(0.0f, -1.0f * time->GetDeltaTime(), 0.0f);
			m_transform->SetPosition(pos);
		}

	}
}

void Dragonfly::ToggleAnimation(void)
{
	if (!playAnimation)
	{
		playAnimation = !playAnimation;
	}
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
	Matrix worldLeft = Matrix::CreateTranslation(m_transform->GetPosition());
	Matrix worldRight = Matrix::CreateTranslation(m_transform->GetPosition());

	if (playAnimation)
	{
		// Draw left wing
		float t = time->GetTotalElapsedTime();
		worldLeft = Matrix::CreateRotationZ(sin(t * 20.0f)) * Matrix::CreateTranslation(m_transform->GetPosition());

		// Draw right wing
		worldRight = Matrix::CreateRotationZ(-sin(t * 20.0f)) * Matrix::CreateTranslation(m_transform->GetPosition());

	}

	m_leftWing->Draw(gfx->GetDeviceContext(), *gfx->GetCommonStates(), worldLeft, view, proj, wireFrame, nullptr);
	m_rightWing->Draw(gfx->GetDeviceContext(), *gfx->GetCommonStates(), worldRight, view, proj, wireFrame, nullptr);

}

void Dragonfly::Reset(void)
{
	upperLimit = false;
	playAnimation = false;
	
	m_transform->SetPosition(m_transform->GetDefaultPosition());
	m_transform->SetRotation(m_transform->GetDefaultRotation());
}