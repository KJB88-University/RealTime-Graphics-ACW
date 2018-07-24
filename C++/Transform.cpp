#include "Transform.h"

using namespace DirectX::SimpleMath;

Transform::Transform(void)
	: m_position(0.0f, 0.0f, 0.0f), m_rotation(0.0f, 0.0f, 0.0f), m_scale(1.0f, 1.0f, 1.0f)
{

}

Transform::Transform(Vector3 position, Vector3 rotation, Vector3 scale)
	: m_position(position), m_rotation(rotation), m_scale(scale)
{

}

Transform::~Transform(void)
{

}

Vector3 Transform::GetPosition(void)
{
	return m_position;
}

Vector3 Transform::GetRotation(void)
{
	return m_rotation;
}

Vector3 Transform::GetScale(void)
{
	return m_scale;
}

void Transform::SetPosition(Vector3 position)
{
	m_position = position;
}

void Transform::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

void Transform::SetRotation(Vector3 rotation)
{
	m_rotation = rotation;
}

void Transform::SetRotation(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
}

void Transform::SetScale(Vector3 scale)
{
	m_scale = scale;
}

void Transform::SetScale(float x, float y, float z)
{
	m_scale.x = x;
	m_scale.y = y;
	m_scale.z = z;
}

