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

Transform* GameObject::GetTransform(void)
{
	return m_transform;
}