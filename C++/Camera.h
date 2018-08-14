#pragma once
// D3D Includes
#include <d3d11.h>

// DXTK Includes
#include <SimpleMath.h>

// ACW Includes
#include "InputManager.h"
#include "TimeManager.h"
#include "GraphicsManager.h"
#include "Transform.h"
#include "Dragonfly.h"

class Camera
{

public:
	Camera(void);
	Camera(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation);
	~Camera(void);

	void Initialize(DirectX::SimpleMath::Vector3 lookAt, float width, float height, float nearClip, float farClip);
	void Destroy(void);
	void Update(InputManager* input, TimeManager* time);
	void Render(GraphicsManager* gm);
	void Reset(void);

	void ToggleFollowCam(GameObject* followObj);

	DirectX::SimpleMath::Matrix& GetViewMatrix();
	DirectX::SimpleMath::Matrix& GetProjMatrix();

private:

	// Movement Modifiers
	const float m_moveSpeed = 5.0f;
	const float m_rotateSpeed = .75f;

	// Delta values
	DirectX::SimpleMath::Vector3 m_vel;
	DirectX::SimpleMath::Vector3 m_angle;

	// Input State
	DirectX::Keyboard::State m_kbState;

	// Transform
	Transform m_transform;

	// Dragonfly
	GameObject* m_followObj;
	bool followCam = false;

	// Camera Matrices
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;
};