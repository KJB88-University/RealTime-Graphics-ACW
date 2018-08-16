#include "GameObject.h"

using namespace DirectX::SimpleMath;

GameObject::GameObject(void)
	: m_transform(nullptr)
{
	m_transform = new Transform();
}

GameObject::GameObject(Vector3& const position, Vector3& const rotation, Vector3& const scale)
	: m_transform(nullptr)
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

Transform* const GameObject::GetTransform(void) const
{
	return m_transform;
}