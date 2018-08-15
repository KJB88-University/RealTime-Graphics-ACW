#pragma once
//#include "GraphicsManager.h"
//#include <string>
//#include "Effects.h"
//
//class Shader : DirectX::BasicEffect
//{
//
//public:
//	Shader();
//	~Shader(void);
//
//	void Initialize(GraphicsManager* gfx, const wchar_t* vShaderFileName, const wchar_t* pShaderFileName);
//	std::string GetName(void);
//
//	// Inherited via IEffect
//	virtual void __cdecl Apply(ID3D11DeviceContext * deviceContext) override;
//	virtual void __cdecl GetVertexShaderBytecode(void const ** pShaderByteCode, size_t * pByteCodeLength) override;
//
//	// Inherited via IEffectLights
//	virtual void SetLightingEnabled(bool value) override;
//	virtual void SetPerPixelLighting(bool value) override;
//
//	virtual void SetLightEnabled(int whichLight, bool value) override;
//	virtual void EnableDefaultLighting() override;
//
//	virtual void XM_CALLCONV SetAmbientLightColor(FXMVECTOR value) override;
//	virtual void XM_CALLCONV SetLightDirection(int whichLight, FXMVECTOR value) override;
//	virtual void XM_CALLCONV SetLightDiffuseColor(int whichLight, FXMVECTOR value) override;
//	virtual void XM_CALLCONV SetLightSpecularColor(int whichLight, FXMVECTOR value) override;
//
//	// Inherited via IEffectMatrices
//	virtual void XM_CALLCONV SetWorld(FXMMATRIX value) override;
//	virtual void XM_CALLCONV SetView(FXMMATRIX value) override;
//	virtual void XM_CALLCONV SetProjection(FXMMATRIX value) override;
//
//	// Vertex color setting.
//	void __cdecl SetVertexColorEnabled(bool value);
//
//	// Texture setting.
//	void __cdecl SetTextureEnabled(bool value);
//	void __cdecl SetTexture(_In_opt_ ID3D11ShaderResourceView* value);
//
//private:
//	// Private implementation.
//	class Impl;
//
//	std::unique_ptr<Impl> pImpl;
//
//	// Prevent copying.
//	Shader(Shader const&);
//	Shader& operator= (Shader const&);
//};