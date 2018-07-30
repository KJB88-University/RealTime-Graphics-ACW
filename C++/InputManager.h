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
	void UpdateStates(void);

	bool IsKeyDown(DirectX::Keyboard::Keys key);
	bool IsKeyUp(DirectX::Keyboard::Keys key);
	bool IsKeyHeld(DirectX::Keyboard::Keys key);

private:

	// Input Devices
	std::unique_ptr<DirectX::Keyboard> m_keyboard;

	// Input States
	DirectX::Keyboard::KeyboardStateTracker m_tracker;
};