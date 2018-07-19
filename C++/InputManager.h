#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "GamePad.h"
class InputManager
{

public:
	InputManager(void);
	~InputManager(void);

	void Initialize(void);
	void Destroy(void);
	void Update(void);

private:

	// Input Devices
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Mouse> m_mouse;
	//std::unique_ptr<DirectX::GamePad> m_gamepad;
};