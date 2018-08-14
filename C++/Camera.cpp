#include "Camera.h"

using namespace DirectX::SimpleMath;

Camera::Camera(void)
	: m_angle(0.0f, 0.0f, 0.0f), m_vel(0.0f, 0.0f, 0.0f)
{
	m_transform = Transform();
}

Camera::Camera(Vector3 position, Vector3 rotation)
	: m_angle(0.0f, 0.0f, 0.0f), m_vel(0.0f, 0.0f, 0.0f)
{
	m_transform = Transform(position, rotation, Vector3(1.0f, 1.0f, 1.0));

}

Camera::~Camera(void)
{

}

void Camera::Initialize(Vector3 lookAt, float width, float height, float nearClip, float farClip)
{
	// Initialize the view matrix
	m_view = Matrix::CreateLookAt(m_transform.GetPosition(), lookAt, Vector3::Up);
	
	// Initialize the projection matrix
	m_proj = Matrix::CreatePerspectiveFieldOfView(DirectX::XM_PIDIV4, width / (FLOAT)height, nearClip, farClip);
}

void Camera::Destroy(void)
{
	// STUB
}

void Camera::Reset(void)
{
	m_transform.SetPosition(m_transform.GetDefaultPosition());
	m_transform.SetRotation(m_transform.GetDefaultRotation());

	m_view = Matrix::CreateLookAt(m_transform.GetPosition(), Vector3(0.0f, 0.0f, -1.0f), Vector3::Up);
}

void Camera::Update(InputManager* input, TimeManager* time)
{
	m_vel = Vector3::Zero;
	m_angle = Vector3::Zero;

	// Panning
	if (!followCam)
	{
		if (input->IsKeyHeld(DirectX::Keyboard::Keys::LeftControl))
		{
			// Pan Forward
			if (input->IsKeyHeld(DirectX::Keyboard::Keys::W))
			{
				m_vel.z += m_moveSpeed * time->GetDeltaTime();
			}

			// Pan Backwards
			else if (input->IsKeyHeld(DirectX::Keyboard::Keys::S))
			{
				m_vel.z -= m_moveSpeed * time->GetDeltaTime();
			}

			// Pan Left
			if (input->IsKeyHeld(DirectX::Keyboard::Keys::A))
			{
				m_vel.x += m_moveSpeed * time->GetDeltaTime();
			}

			// Pan Right
			else if (input->IsKeyHeld(DirectX::Keyboard::Keys::D))
			{
				m_vel.x -= m_moveSpeed * time->GetDeltaTime();
			}

			if (input->IsKeyHeld(DirectX::Keyboard::Keys::PageUp))
			{
				m_vel.y -= m_moveSpeed * time->GetDeltaTime();
			}

			else if (input->IsKeyHeld(DirectX::Keyboard::Keys::PageDown))
			{
				m_vel.y += m_moveSpeed * time->GetDeltaTime();
			}

		}

		// Rotation
		else
		{
			// Rotate Down
			if (input->IsKeyHeld(DirectX::Keyboard::Keys::W))
			{
				m_angle.x -= m_rotateSpeed * time->GetDeltaTime();
			}

			// Rotate Up
			else if (input->IsKeyHeld(DirectX::Keyboard::Keys::S))
			{
				m_angle.x += m_rotateSpeed * time->GetDeltaTime();
			}

			// Rotate Left
			if (input->IsKeyHeld(DirectX::Keyboard::Keys::A))
			{
				m_angle.y -= m_rotateSpeed * time->GetDeltaTime();
			}

			// Rotate Right
			else if (input->IsKeyHeld(DirectX::Keyboard::Keys::D))
			{
				m_angle.y += m_rotateSpeed * time->GetDeltaTime();
			}
		}

		// Update transform with delta values
		m_transform.SetPosition(m_transform.GetPosition() + m_vel);
		m_transform.SetRotation(m_transform.GetRotation() + m_angle);
	}
} 

void Camera::Render(GraphicsManager* gm)
{
	if (!followCam)
	{
		m_view = Matrix::CreateFromYawPitchRoll(m_transform.GetRotation().y, m_transform.GetRotation().x, m_transform.GetRotation().z) * Matrix::CreateTranslation(m_transform.GetPosition());
	}
	else
	{
		m_view = Matrix::CreateFromYawPitchRoll(m_transform.GetRotation().y, m_transform.GetRotation().x, m_transform.GetRotation().z)
			* Matrix::CreateTranslation(
				Vector3
				(
					m_followObj->GetTransform()->GetPosition().x,
					-m_followObj->GetTransform()->GetPosition().y,
					m_followObj->GetTransform()->GetPosition().z
				)
			);
	}
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

void Camera::ToggleFollowCam(GameObject* followObj)
{
	m_followObj = followObj;
	followCam = true;
}