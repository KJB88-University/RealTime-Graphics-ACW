#include "Camera.h"

using namespace DirectX::SimpleMath;

Camera::Camera(void)
	: m_vel(0.0f, 0.0f, 0.0f), m_angle(0.0f, 0.0f, 0.0f), m_followObj(nullptr)
{
	m_transform = Transform();
}

Camera::Camera(const Vector3& position, const Vector3& rotation)
	: m_vel(0.0f, 0.0f, 0.0f), m_angle(0.0f, 0.0f, 0.0f), m_followObj(nullptr)
{
	m_transform = Transform(position, rotation, Vector3(1.0f, 1.0f, 1.0f));

}

Camera::~Camera(void)
{

}

void Camera::Initialize(const Vector3& const lookAt, float const width, float const height, float const nearClip, float const farClip)
{
	// Initialize the view matrix
	m_view = Matrix::CreateLookAt(m_transform.GetPosition(), lookAt, Vector3::Up);
	
	// Initialize the projection matrix
	m_proj = Matrix::CreatePerspectiveFieldOfView(DirectX::XM_PIDIV4, static_cast<float>(width / height), nearClip, farClip);
}

//void Camera::Destroy(void)
//{
//	// STUB
//}

//void Camera::Reset(void)
//{
//
//	m_transform.SetPosition(m_transform.GetDefaultPosition());
//	m_transform.SetRotation(-m_transform.GetDefaultRotation());
//
//	m_view = Matrix::CreateLookAt(m_transform.GetPosition(), Vector3(0.0f, 0.0f, -1.0f), Vector3::Up);
//}

void Camera::Update(const InputManager* const input, const TimeManager* const time)
{
	m_vel = Vector3::Zero;
	m_angle = Vector3::Zero;

	// Panning
	if (!followCam)
	{
		if (input->IsKeyHeld(DirectX::Keyboard::Keys::LeftControl))
		{
			// Pan Forward
			if (input->IsKeyHeld(DirectX::Keyboard::Keys::Up))
			{
				m_vel.z += m_moveSpeed * time->GetDeltaTime();
			}

			// Pan Backwards
			else if (input->IsKeyHeld(DirectX::Keyboard::Keys::Down))
			{
				m_vel.z -= m_moveSpeed * time->GetDeltaTime();
			}

			// Pan Left
			if (input->IsKeyHeld(DirectX::Keyboard::Keys::Left))
			{
				m_vel.x += m_moveSpeed * time->GetDeltaTime();
			}

			// Pan Right
			else if (input->IsKeyHeld(DirectX::Keyboard::Keys::Right))
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
			if (input->IsKeyHeld(DirectX::Keyboard::Keys::Up))
			{
				m_angle.x -= m_rotateSpeed * time->GetDeltaTime();
			}

			// Rotate Up
			else if (input->IsKeyHeld(DirectX::Keyboard::Keys::Down))
			{
				m_angle.x += m_rotateSpeed * time->GetDeltaTime();
			}

			// Rotate Left
			if (input->IsKeyHeld(DirectX::Keyboard::Keys::Left))
			{
				m_angle.y -= m_rotateSpeed * time->GetDeltaTime();
			}

			// Rotate Right
			else if (input->IsKeyHeld(DirectX::Keyboard::Keys::Right))
			{
				m_angle.y += m_rotateSpeed * time->GetDeltaTime();
			}
		}

		// Update transform with delta values
		Vector3 pos = m_transform.GetPosition();
		m_transform.SetPosition(m_transform.GetPosition() + m_vel);
		m_transform.SetRotation(m_transform.GetRotation() + m_angle);
		pos = m_transform.GetPosition();
	}
} 

void Camera::Render(const GraphicsManager* const gm)
{
	if (!followCam)
	{
		m_view = Matrix::CreateFromYawPitchRoll(m_transform.GetRotation().y, m_transform.GetRotation().x, 0.0f) * Matrix::CreateTranslation(m_transform.GetPosition());
	}
	else
	{
		m_view = Matrix::CreateFromYawPitchRoll(m_transform.GetRotation().y, m_transform.GetRotation().x, 0.0f)
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


const Matrix& Camera::GetViewMatrix() const
{
	return m_view;
}

const Matrix& Camera::GetProjMatrix() const
{
	return m_proj;
}

void Camera::ToggleFollowCam(GameObject* const followObj)
{
	m_followObj = followObj;
	followCam = true;
}