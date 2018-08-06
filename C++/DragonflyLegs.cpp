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
	m_legs.reset(DirectX::Model::CreateFromSDKMESH(gfx->GetDevice(), L"", *gfx->GetFXFactory()).release());
}

void DragonflyLegs::Destroy(void)
{

}

void DragonflyLegs::Update(TimeManager* time)
{

}

void DragonflyLegs::Render(GraphicsManager* gfx, Matrix* world, Matrix* proj, Matrix* view, bool wireFrame)
{

}
