//#pragma once
//// D3D Includes
//#include <d3d11.h>
//
//// DXTK Includes
//#include <SimpleMath.h>
//#include <Model.h>
//
//// ACW Includes
//#include "GameObject.h"
//
//class DragonflyLegs : GameObject
//{
//
//public:
//
//	DragonflyLegs(void);
//	DragonflyLegs(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation, DirectX::SimpleMath::Vector3 scale);
//	DragonflyLegs(const DragonflyLegs& other);
//	~DragonflyLegs(void);
//
//	virtual void Initialize(GraphicsManager* gfx) override;
//	virtual void Destroy(void) override;
//	virtual Transform* GetTransform(void) override;
//
//	void Update(TimeManager* time);
//	void Render(GraphicsManager* gfx, DirectX::SimpleMath::Matrix proj, DirectX::SimpleMath::Matrix view, bool wireFrame);
//
//private:
//
//	std::unique_ptr<DirectX::Model> m_legs;
//};