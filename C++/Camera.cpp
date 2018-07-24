#include "Camera.h"

using namespace DirectX::SimpleMath;


Camera::Camera(void)
	: m_position(0.0f, 0.0f, 0.0f), m_rotation(0.0f, 0.0f, -1.0f), m_angle(0.0f, 0.0f, 0.0f), m_vel(0.0f, 0.0f, 0.0f)
{

}

Camera::Camera(Vector3 position, Vector3 rotation)
	: m_position(position), m_rotation(rotation), m_angle(0.0f, 0.0f, 0.0f), m_vel(0.0f, 0.0f, 0.0f)
{

}
Camera::~Camera(void)
{

}

void Camera::Initialize(float width, float height, float nearClip, float farClip)
{
	Vector3 startView = Vector3(0.0f, 0.0f, -10.0f);

	// Initialize the view matrix
	m_view = Matrix::CreateLookAt(m_position, startView, Vector3::Up);
	
	// Initialize the projection matrix
	m_proj = Matrix::CreatePerspectiveFieldOfView(DirectX::XM_PIDIV4, width / (FLOAT)height, nearClip, farClip);
	//m_proj = DirectX::XMMatrixTranspose(m_proj);
}

void Camera::Destroy(void)
{

}

void Camera::Update(InputManager* input, TimeManager* time)
{
	m_vel = Vector3::Zero;
	m_angle = Vector3::Zero;

	m_kbState = input->GetKeyboardState();

	// Panning
	if (m_kbState.LeftControl)
	{
		// Pan Forward
		if (m_kbState.W)
		{
			m_vel.z += +m_moveSpeed * time->GetDeltaTime();
		}
		 
		// Pan Backwards
		else if (m_kbState.S)
		{
			m_vel.z += -m_moveSpeed * time->GetDeltaTime();
		}

		// Pan Left
		if (m_kbState.A)
		{
			m_vel.x += m_moveSpeed * time->GetDeltaTime();
		}

		// Pan Right
		else if (m_kbState.D)
		{
			m_vel.x += -m_moveSpeed * time->GetDeltaTime();
		}

		if (m_kbState.PageUp)
		{
			m_vel.y += -m_moveSpeed * time->GetDeltaTime();
		}

		else if (m_kbState.PageDown)
		{
			m_vel.y += +m_moveSpeed * time->GetDeltaTime();
		}

	}

	// Rotation
	else
	{
		// Rotate Down
		if (m_kbState.W)
		{
			m_angle.x += m_rotateSpeed * time->GetDeltaTime();
		}

		// Rotate Up
		else if (m_kbState.S)
		{
			m_angle.x += -m_rotateSpeed * time->GetDeltaTime();
		}

		// Rotate Left
		if (m_kbState.A)
		{
			m_angle.y += -m_rotateSpeed * time->GetDeltaTime();
		}

		// Rotate Right
		else if (m_kbState.D)
		{
			m_angle.y += m_rotateSpeed * time->GetDeltaTime();
		}
	}

	// Update transform with delta values
	m_position += m_vel;
	m_rotation += m_angle;
} 

void Camera::Render(GraphicsManager* gm)
{

	m_view = Matrix::CreateTranslation(m_position) * Matrix::CreateFromYawPitchRoll(m_rotation.y, m_rotation.x, 0.0f);
	gm->GetBasicEffect()->SetView(m_view);

}


Matrix& Camera::GetViewMatrix()
{
	return m_view;
}

Matrix& Camera::GetProjMatrix()
{
	return m_proj;
}
