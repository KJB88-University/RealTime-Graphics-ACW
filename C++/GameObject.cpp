#include "GameObject.h"

using namespace DirectX::SimpleMath;

GameObject::GameObject(void)
{
	m_transform = new Transform();
}

GameObject::GameObject(Vector3 position, Vector3 rotation, Vector3 scale)
{
	m_transform = new Transform();

	m_transform->SetPosition(position);
	m_transform->SetRotation(rotation);
	m_transform->SetScale(scale);
}

GameObject::~GameObject(void)
{
	delete m_transform;
	m_transform = nullptr;
}

void GameObject::Initialize(GraphicsManager* gfx)
{
	// STUB
}

void GameObject::Update(TimeManager* time)
{
	// STUB
}

void GameObject::Render(GraphicsManager* gfx, Matrix proj, Matrix view)
{
	// STUB
}

Transform* GameObject::GetTransform(void)
{
	return m_transform;
}