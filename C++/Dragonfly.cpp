#include "Dragonfly.h"
using namespace DirectX::SimpleMath;

Dragonfly::Dragonfly(void)
	: GameObject()
{

}

Dragonfly::Dragonfly(Vector3& const position, Vector3& const rotation, Vector3& const scale)
	: GameObject(position, rotation, scale)
{

}

Dragonfly::~Dragonfly(void)
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

void Dragonfly::Initialize(GraphicsManager* const gfx)
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
}

void Dragonfly::Destroy(void)
{
	// STUB
}

void Dragonfly::Update(const TimeManager* const time)
{
	if (playAnimation)
	{
		if (GetTransform()->GetPosition().y >= 10.0f)
		{
			upperLimit = true;
		}
		else if (GetTransform()->GetPosition().y < 2.25f)
		{
			playAnimation = false;
			upperLimit = false;
		}
		// Flying up
		if (!upperLimit)
		{
			Vector3 pos = GetTransform()->GetPosition();
			pos += Vector3(0.0f, 1.0f * time->GetDeltaTime(), 0.0f);
			GetTransform()->SetPosition(pos);
		}
		
		// Flying down
		else
		{
			Vector3 pos = GetTransform()->GetPosition();
			pos += Vector3(0.0f, -1.0f * time->GetDeltaTime(), 0.0f);
			GetTransform()->SetPosition(pos);
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

void Dragonfly::Render(const GraphicsManager* const gfx, const TimeManager* const time, const Matrix& proj, const Matrix& view, bool const wireFrame) const
{
	Matrix world = Matrix::Identity;
	world = Matrix::CreateTranslation(GetTransform()->GetPosition());

	// Draw body
	m_body->Draw(gfx->GetDeviceContext(), *gfx->GetCommonStates(), world, view, proj, wireFrame, nullptr);

	// Draw legs
	world = Matrix::CreateTranslation
	(
		Vector3
		(
			GetTransform()->GetPosition().x,
			GetTransform()->GetPosition().y - 0.25f,
			GetTransform()->GetPosition().z + 0.75f
		)
	);

	m_frontLegs->Draw(gfx->GetDeviceContext(), *gfx->GetCommonStates(), world, view, proj, wireFrame, nullptr);
	m_midLegs->Draw(gfx->GetDeviceContext(), *gfx->GetCommonStates(), world, view, proj, wireFrame, nullptr);
	m_backLegs->Draw(gfx->GetDeviceContext(), *gfx->GetCommonStates(), world, view, proj, wireFrame, nullptr);

	Matrix worldLeft = Matrix::CreateTranslation(GetTransform()->GetPosition());
	Matrix worldRight = Matrix::CreateTranslation(GetTransform()->GetPosition());

	if (playAnimation)
	{
		// Draw left wing
		worldLeft = Matrix::CreateRotationZ(sin(time->GetTotalElapsedTime() * 20.0f)) * Matrix::CreateTranslation(GetTransform()->GetPosition());

		// Draw right wing
		worldRight = Matrix::CreateRotationZ(-sin(time->GetTotalElapsedTime() * 20.0f)) * Matrix::CreateTranslation(GetTransform()->GetPosition());

	}

	m_leftWing->Draw(gfx->GetDeviceContext(), *gfx->GetCommonStates(), worldLeft, view, proj, wireFrame, nullptr);
	m_rightWing->Draw(gfx->GetDeviceContext(), *gfx->GetCommonStates(), worldRight, view, proj, wireFrame, nullptr);

}

void Dragonfly::Reset(void)
{
	upperLimit = false;
	playAnimation = false;

	GetTransform()->SetPosition
	(
		GetTransform()->GetDefaultPosition().x,
		GetTransform()->GetDefaultPosition().y,
		GetTransform()->GetDefaultPosition().z
	);

	GetTransform()->SetRotation(GetTransform()->GetDefaultRotation());
}