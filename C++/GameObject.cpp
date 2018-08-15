#include "GameObject.h"

using namespace DirectX::SimpleMath;

GameObject::GameObject(void)
{
	m_transform = new Transform();
}

GameObject::GameObject(const GameObject& other)
	: m_transform(other.m_transform)
{

}

GameObject::GameObject(Vector3& const position, Vector3& const rotation, Vector3& const scale)
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

Transform* GameObject::GetTransform(void) const
{
	return m_transform;
}