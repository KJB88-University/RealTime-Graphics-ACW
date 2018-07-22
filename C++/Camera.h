#pragma once
// D3D Includes
#include <d3d11.h>

// DXTK Includes
#include <SimpleMath.h>

// ACW Includes
#include "InputManager.h"
#include "TimeManager.h"

class Camera
{

public:
	Camera(void);
	Camera(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation);
	~Camera(void);

	void Initialize(float width, float height, float nearClip, float farClip);
	void Destroy(void);
	void Update(InputManager* input, TimeManager* time);
	void Render(void);

	DirectX::SimpleMath::Matrix& GetViewMatrix();
	DirectX::SimpleMath::Matrix& GetProjMatrix();

private:

	// Movement Modifiers
	float m_moveSpeed = 2.0f;
	float m_rotateSpeed = 0.35f;

	// Delta values
	DirectX::SimpleMath::Vector3 m_vel;
	DirectX::SimpleMath::Vector3 m_angVel;

	// Input State
	DirectX::Keyboard::State m_kbState;

	// Transform
	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_rotation;

	// Camera Matrices
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;
};