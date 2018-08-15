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
	Camera(DirectX::SimpleMath::Vector3& const position, DirectX::SimpleMath::Vector3& const rotation);
	~Camera(void);

	void Initialize(DirectX::SimpleMath::Vector3& const lookAt, float const width, float const height, float const nearClip, float const farClip);
	//void Destroy(void);
	void Update(const InputManager* const input, const TimeManager* const time);
	void Render(const GraphicsManager* const gm);
	//void Reset(void);

	void ToggleFollowCam(GameObject* followObj);

	const DirectX::SimpleMath::Matrix& GetViewMatrix() const;
	const DirectX::SimpleMath::Matrix& GetProjMatrix() const;

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

	Camera(const Camera& other) = delete;
	Camera& Camera::operator=(Camera& other) = delete;
};