#pragma once
// D3D Includes
#include <d3d11.h>

// DXTK Includes
#include <SimpleMath.h>

class Camera
{

public:
	Camera(void);
	Camera(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation);
	~Camera(void);

	void Initialize(float width, float height, float nearClip, float farClip);
	void Destroy(void);
	void Update(void);
	void Render(void);

	DirectX::SimpleMath::Matrix& GetViewMatrix();
	DirectX::SimpleMath::Matrix& GetProjMatrix();

private:

	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_rotation;

	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;
};