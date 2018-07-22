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

	DirectX::Keyboard::State& GetKeyboardState() const;
	//DirectX::Mouse::State& GetMouseState() const;

private:

	// Input Devices
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	//std::unique_ptr<DirectX::Mouse> m_mouse;
	//std::unique_ptr<DirectX::GamePad> m_gamepad;

	// Input States
	DirectX::Keyboard::State m_kbState;
	//DirectX::Mouse::State m_mouseState;
};