#include "Camera.h"

using namespace DirectX::SimpleMath;

Camera::Camera(void)
	: m_position(0.0f, 0.0f, 0.0f), m_rotation(0.0f, 0.0f, -1.0f)
{

}

Camera::Camera(Vector3 position, Vector3 rotation)
	:m_position(position), m_rotation(rotation)
{

}
Camera::~Camera(void)
{

}

void Camera::Initialize(float width, float height, float nearClip, float farClip)
{
	// Initialize the view matrix
	m_view = Matrix::CreateLookAt(m_position, m_rotation, Vector3::Up);

	// Initialize the projection matrix
	m_proj = Matrix::CreatePerspectiveFieldOfView(DirectX::XM_PIDIV4, width / (FLOAT)height, nearClip, farClip);
}

void Camera::Destroy(void)
{

}

void Camera::Update(void)
{

}

void Camera::Render(void)
{

}


Matrix& Camera::GetViewMatrix()
{
	return m_view;
}

Matrix& Camera::GetProjMatrix()
{
	return m_proj;
}
