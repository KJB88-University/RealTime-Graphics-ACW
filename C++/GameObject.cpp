#include "GameObject.h"

using namespace DirectX::SimpleMath;

GameObject::GameObject(void)
{
	m_transform = new Transform();
}

GameObject::GameObject(const GameObject& other)
{

}

GameObject::GameObject(Vector3 position, Vector3 rotation, Vector3 scale)
{
	m_transform = new Transform(position, rotation, scale);
}

GameObject::~GameObject(void)
{
	delete m_transform;
	m_transform = nullptr;
}

void GameObject::Reset(void)
{

}

Transform* GameObject::GetTransform(void)
{
	return m_transform;
}