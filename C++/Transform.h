#pragma once
// D3D Includes
#include <d3d11.h>

// DXTK Includes
#include <SimpleMath.h>

class Transform
{
public:

	Transform(void);
	Transform(
		DirectX::SimpleMath::Vector3 position, 
		DirectX::SimpleMath::Vector3 rotation, 
		DirectX::SimpleMath::Vector3 scale
	);
	~Transform(void);

	DirectX::SimpleMath::Vector3 GetPosition(void);
	DirectX::SimpleMath::Vector3 GetRotation(void);
	DirectX::SimpleMath::Vector3 GetScale(void);

	void SetPosition(DirectX::SimpleMath::Vector3 position);
	void SetPosition(float x, float y, float z);

	void SetRotation(DirectX::SimpleMath::Vector3 rotation);
	void SetRotation(float x, float y, float z);

	void SetScale(DirectX::SimpleMath::Vector3 scale);
	void SetScale(float x, float y, float z);

private:

	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_rotation;
	DirectX::SimpleMath::Vector3 m_scale;
};