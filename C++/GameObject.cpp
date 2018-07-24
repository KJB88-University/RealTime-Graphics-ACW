#include "GameObject.h"

GameObject::GameObject(void)
	: m_transform()
{

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