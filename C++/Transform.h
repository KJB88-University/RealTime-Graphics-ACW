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
		const DirectX::SimpleMath::Vector3& const position,
		const DirectX::SimpleMath::Vector3& const rotation,
		const DirectX::SimpleMath::Vector3& const scale
	);
	~Transform(void);

	const DirectX::SimpleMath::Vector3& GetPosition(void) const;
	const float const GetPositionX(void) const;
	const float const GetPositionY(void) const;
	const float const GetPositionZ(void) const;

	const DirectX::SimpleMath::Vector3& GetRotation(void) const;
	const float const GetRotationX(void) const;
	const float const GetRotationY(void) const;
	const float const GetRotationZ(void) const;

	const DirectX::SimpleMath::Vector3& GetScale(void) const;
	const float const GetScaleX(void) const;
	const float const GetScaleY(void) const;
	const float const GetScaleZ(void) const;

	void SetPosition(const DirectX::SimpleMath::Vector3& const position);
	void SetPosition(const float const x, const float const y, const float const z);

	void SetRotation(const DirectX::SimpleMath::Vector3& const rotation);
	void SetRotation(const float const x, const float const y, const float const z);

	void SetScale(const DirectX::SimpleMath::Vector3& const scale);
	void SetScale(const float const x, const float const y, const float const z);

	const DirectX::SimpleMath::Vector3& GetDefaultPosition(void) const;
	const float& const GetDefaultPositionX(void) const;
	const float& const GetDefaultPositionY(void) const;
	const float& const GetDefaultPositionZ(void) const;

	const DirectX::SimpleMath::Vector3& GetDefaultRotation(void) const;
	const float& const GetDefaultRotationX(void) const;
	const float& const GetDefaultRotationY(void) const;
	const float& const GetDefaultRotationZ(void) const;

	const DirectX::SimpleMath::Vector3& GetDefaultScale(void) const;
	const float& const GetDefaultScaleX(void) const;
	const float& const GetDefaultScaleY(void) const;
	const float& const GetDefaultScaleZ(void) const;

	void SetDefaultPosition(const DirectX::SimpleMath::Vector3& const position);
	void SetDefaultPosition(const float const x, const float const y, const float const z);

	void SetDefaultRotation(const DirectX::SimpleMath::Vector3& const rotation);
	void SetDefaultRotation(const float const x, const float const y, const float const z);

	void SetDefaultScale(const DirectX::SimpleMath::Vector3& const scale);
	void SetDefaultScale(const float const x, const float const y, const float const z);

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
