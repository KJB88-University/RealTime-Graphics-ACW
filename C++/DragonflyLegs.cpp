#include "DragonflyLegs.h"

using namespace DirectX::SimpleMath;

DragonflyLegs::DragonflyLegs(void)
	: GameObject()
{

}

DragonflyLegs::DragonflyLegs(Vector3 position, Vector3 rotation, Vector3 scale)
	: GameObject(position, rotation, scale)
{

}

DragonflyLegs::DragonflyLegs(const DragonflyLegs& other)
{

}

DragonflyLegs::~DragonflyLegs(void)
{

}

void DragonflyLegs::Initialize(GraphicsManager* gfx)
{
	m_legs.reset(DirectX::Model::CreateFromSDKMESH(gfx->GetDevice(), L"DFlegs.sdkmesh", *gfx->GetFXFactory()).release());
}

void DragonflyLegs::Destroy(void)
{

}

Transform* DragonflyLegs::GetTransform(void)
{
	return m_transform;
}

void DragonflyLegs::Update(TimeManager* time, Transform* transf)
{
	m_transform->SetPosition(transf->GetPosition());
}

void DragonflyLegs::Render(GraphicsManager* gfx, Matrix world, Matrix proj, Matrix view, bool wireFrame)
{

	m_legs->Draw(gfx->GetDeviceContext(), *gfx->GetCommonStates(), world, proj, view, wireFrame, nullptr);
}
