#include "Transform.h"

using namespace DirectX::SimpleMath;

Transform::Transform(void)
	: m_position(0.0f, 0.0f, 0.0f), m_rotation(0.0f, 0.0f, 0.0f), m_scale(1.0f, 1.0f, 1.0f),
	m_defaultPosition(0.0f, 0.0f, 0.0f), m_defaultRotation(0.0f, 0.0f, 0.0f), m_defaultScale(1.0f, 1.0f, 1.0f)
{

}

Transform::Transform(const Vector3& const position, const Vector3& const rotation, const Vector3& const scale)
	: m_position(position), m_rotation(rotation), m_scale(scale), m_defaultPosition(position), m_defaultRotation(rotation), m_defaultScale(scale)
{

}

Transform::~Transform(void)
{

}

const Vector3& Transform::GetPosition(void) const
{
	return m_position;
}

const Vector3& Transform::GetRotation(void) const
{
	return m_rotation;
}

const Vector3& Transform::GetScale(void) const
{
	return m_scale;
}

void Transform::SetPosition(const Vector3& const position)
{
	m_position = position;
}

void Transform::SetPosition(float const x, float const y, float const z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

void Transform::SetRotation(const Vector3& const rotation)
{
	m_rotation = rotation;
}

void Transform::SetRotation(float const x, float const y, float const z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
}

void Transform::SetScale(const Vector3& const scale)
{
	m_scale = scale;
}

void Transform::SetScale(float const x, float const y, float const z)
{
	m_scale.x = x;
	m_scale.y = y;
	m_scale.z = z;
}

const DirectX::SimpleMath::Vector3& Transform::GetDefaultPosition(void) const
{
	return m_defaultPosition;
}

const DirectX::SimpleMath::Vector3& Transform::GetDefaultRotation(void) const
{
	return m_defaultPosition;
}

const DirectX::SimpleMath::Vector3& Transform::GetDefaultScale(void) const
{
	return m_defaultScale;
}

void Transform::SetDefaultPosition(const Vector3& const position)
{
	m_defaultPosition = position;
}

void Transform::SetDefaultPosition(float const x, float const y, float const z)
{
	m_defaultPosition.x = x;
	m_defaultPosition.y = y;
	m_defaultPosition.z = z;
}

void Transform::SetDefaultRotation(const Vector3& const rotation)
{
	m_defaultRotation = rotation;
}

void Transform::SetDefaultRotation(float const x, float const y, float const z)
{
	m_defaultRotation.x = x;
	m_defaultRotation.y = y;
	m_defaultRotation.z = z;
}

void Transform::SetDefaultScale(const Vector3& const scale)
{
	m_defaultScale = scale;
}

void Transform::SetDefaultScale(float const x, float const y, float const z)
{
	m_defaultScale.x = x;
	m_defaultScale.y = y;
	m_defaultScale.z = z;
}

