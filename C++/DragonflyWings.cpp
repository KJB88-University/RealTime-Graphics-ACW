#include "DragonflyWings.h"

using namespace DirectX::SimpleMath;

DragonflyWings::DragonflyWings(LPWSTR fileName, LPWSTR fileName2)
	: GameObject()
{

}

DragonflyWings::DragonflyWings(Vector3 position, Vector3 rotation, Vector3 scale)
	: GameObject(position, rotation, scale)
{

}

DragonflyWings::DragonflyWings(const DragonflyWings& other)
{

}

DragonflyWings::~DragonflyWings(void)
{

}

Transform* DragonflyWings::GetTransform(void)
{
	return m_transform;
}

void DragonflyWings::Initialize(GraphicsManager* gfx)
{
	m_left.reset(DirectX::Model::CreateFromSDKMESH(gfx->GetDevice(), L"DFleftwing.sdkmesh", *gfx->GetFXFactory()).release());
	m_right.reset(DirectX::Model::CreateFromSDKMESH(gfx->GetDevice(), L"DFrightwing.sdkmesh", *gfx->GetFXFactory()).release());
}

void DragonflyWings::Destroy(void)
{

}

void DragonflyWings::Update(TimeManager* time, Transform* transf)
{
	m_transform->SetPosition(transf->GetPosition());
}

void DragonflyWings::Render(GraphicsManager* gfx, Matrix world, Matrix proj, Matrix view, bool wireFrame)
{

	m_right->Draw(gfx->GetDeviceContext(), *gfx->GetCommonStates(), world, proj, view, wireFrame, nullptr);
	m_left->Draw(gfx->GetDeviceContext(), *gfx->GetCommonStates(), world, proj, view, wireFrame, nullptr);
}
