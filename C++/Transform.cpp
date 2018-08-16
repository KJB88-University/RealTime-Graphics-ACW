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

const Vector3& const Transform::GetPosition(void) const
{
	return m_position;
}

const float const Transform::GetPositionX(void) const
{
	return m_position.x;
}

const float const Transform::GetPositionY(void) const
{
	return m_position.y;
}

const float const Transform::GetPositionZ(void) const
{
	return m_position.z;
}

const Vector3& const Transform::GetRotation(void) const
{
	return m_rotation;
}

const float const Transform::GetRotationX(void) const
{
	return m_rotation.x;
}

const float const Transform::GetRotationY(void) const
{
	return m_rotation.y;
}

const float const Transform::GetRotationZ(void) const
{
	return m_rotation.z;
}

const Vector3& const Transform::GetScale(void) const
{
	return m_scale;
}

const float const Transform::GetScaleX(void) const
{
	return m_scale.x;
}

const float const Transform::GetScaleY(void) const
{
	return m_scale.y;
}

const float const Transform::GetScaleZ(void) const
{
	return m_scale.z;
}

void Transform::SetPosition(const Vector3& const position)
{
	m_position = position;
}

void Transform::SetPosition(const float x, const float y, const float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

void Transform::SetRotation(const Vector3& const rotation)
{
	m_rotation = rotation;
}

void Transform::SetRotation(const float x, const float y, const float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
}

void Transform::SetScale(const Vector3& const scale)
{
	m_scale = scale;
}

void Transform::SetScale(const float x, const float y, const float z)
{
	m_scale.x = x;
	m_scale.y = y;
	m_scale.z = z;
}

const Vector3& const Transform::GetDefaultPosition(void) const
{
	return m_defaultPosition;
}

const float& const Transform::GetDefaultPositionX(void) const
{
	return m_defaultPosition.x;
}

const float& const Transform::GetDefaultPositionY(void) const
{
	return m_defaultPosition.y;
}

const float& const Transform::GetDefaultPositionZ(void) const
{
	return m_defaultPosition.z;
}

const Vector3& const Transform::GetDefaultRotation(void) const
{
	return m_defaultRotation;
}

const float& const Transform::GetDefaultRotationX(void) const
{
	return m_defaultRotation.x;
}

const float& const Transform::GetDefaultRotationY(void) const
{
	return m_defaultRotation.y;
}

const float& const Transform::GetDefaultRotationZ(void) const
{
	return m_defaultRotation.z;
}

const Vector3& const Transform::GetDefaultScale(void) const
{
	return m_defaultScale;
}

const float& const Transform::GetDefaultScaleX(void) const
{
	return m_defaultScale.x;
}

const float& const Transform::GetDefaultScaleY(void) const
{
	return m_defaultScale.y;
}


const float& const Transform::GetDefaultScaleZ(void) const
{
	return m_defaultScale.z;
}


void Transform::SetDefaultPosition(const Vector3& const position)
{
	m_defaultPosition = position;
}

void Transform::SetDefaultPosition(const float x, const float y, const float z)
{
	m_defaultPosition.x = x;
	m_defaultPosition.y = y;
	m_defaultPosition.z = z;
}

void Transform::SetDefaultRotation(const Vector3& const rotation)
{
	m_defaultRotation = rotation;
}

void Transform::SetDefaultRotation(const float x, const float y, const float z)
{
	m_defaultRotation.x = x;
	m_defaultRotation.y = y;
	m_defaultRotation.z = z;
}

void Transform::SetDefaultScale(const Vector3& const scale)
{
	m_defaultScale = scale;
}

void Transform::SetDefaultScale(const float x, const float y, const float z)
{
	m_defaultScale.x = x;
	m_defaultScale.y = y;
	m_defaultScale.z = z;
}

