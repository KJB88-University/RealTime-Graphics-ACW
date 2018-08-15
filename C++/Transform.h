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
		DirectX::SimpleMath::Vector3& const position,
		DirectX::SimpleMath::Vector3& const rotation,
		DirectX::SimpleMath::Vector3& const scale
	);
	~Transform(void);

	const DirectX::SimpleMath::Vector3& GetPosition(void) const;
	const DirectX::SimpleMath::Vector3& GetRotation(void) const;
	const DirectX::SimpleMath::Vector3& GetScale(void) const;

	void SetPosition(DirectX::SimpleMath::Vector3& const position);
	void SetPosition(float const x, float const y, float const z);

	void SetRotation(DirectX::SimpleMath::Vector3& const rotation);
	void SetRotation(float const x, float const y, float const z);

	void SetScale(DirectX::SimpleMath::Vector3& const scale);
	void SetScale(float const x, float const y, float const z);

	const DirectX::SimpleMath::Vector3& GetDefaultPosition(void) const;
	const DirectX::SimpleMath::Vector3& GetDefaultRotation(void) const;
	const DirectX::SimpleMath::Vector3& GetDefaultScale(void) const;

	void SetDefaultPosition(DirectX::SimpleMath::Vector3& const position);
	void SetDefaultPosition(float  constx, float  consty, float const z);

	void SetDefaultRotation(DirectX::SimpleMath::Vector3& const rotation);
	void SetDefaultRotation(float const x, float  consty, float const z);

	void SetDefaultScale(DirectX::SimpleMath::Vector3& const scale);
	void SetDefaultScale(float  constx, float  consty, float  constz);

private:

	// Current Values
	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_rotation;
	DirectX::SimpleMath::Vector3 m_scale;

	// Default Values
	DirectX::SimpleMath::Vector3 m_defaultPosition;
	DirectX::SimpleMath::Vector3 m_defaultRotation;
	DirectX::SimpleMath::Vector3 m_defaultScale;
};
