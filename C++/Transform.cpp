#include "Transform.h"

using namespace DirectX::SimpleMath;

Transform::Transform(void)
	: m_position(0.0f, 0.0f, 0.0f), m_rotation(0.0f, 0.0f, 0.0f), m_scale(1.0f, 1.0f, 1.0f), m_defaultPosition(m_position), m_defaultRotation(m_rotation), m_defaultScale(m_scale)
{

}

Transform::Transform(Vector3 position, Vector3 rotation, Vector3 scale)
	: m_position(position), m_rotation(rotation), m_scale(scale), m_defaultPosition(position), m_defaultRotation(rotation), m_defaultScale(scale)
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

DirectX::SimpleMath::Vector3 Transform::GetDefaultPosition(void)
{
	return m_defaultPosition;
}

DirectX::SimpleMath::Vector3 Transform::GetDefaultRotation(void)
{
	return m_defaultPosition;
}

DirectX::SimpleMath::Vector3 Transform::GetDefaultScale(void)
{
	return m_defaultScale;
}

void Transform::SetDefaultPosition(DirectX::SimpleMath::Vector3 position)
{
	m_defaultPosition = position;
}

void Transform::SetDefaultPosition(float x, float y, float z)
{
	m_defaultPosition.x = x;
	m_defaultPosition.y = y;
	m_defaultPosition.z = z;
}

void Transform::SetDefaultRotation(DirectX::SimpleMath::Vector3 rotation)
{
	m_defaultRotation = rotation;
}

void Transform::SetDefaultRotation(float x, float y, float z)
{
	m_defaultRotation.x = x;
	m_defaultRotation.y = y;
	m_defaultRotation.z = z;
}

void Transform::SetDefaultScale(DirectX::SimpleMath::Vector3 scale)
{
	m_defaultScale = scale;
}

void Transform::SetDefaultScale(float x, float y, float z)
{
	m_defaultScale.x = x;
	m_defaultScale.y = y;
	m_defaultScale.z = z;
}

