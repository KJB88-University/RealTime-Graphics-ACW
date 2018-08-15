#include "InputManager.h"

using namespace DirectX;

InputManager::InputManager(void)
	:m_keyboard(nullptr)
{

}

InputManager::~InputManager(void)
{

}

void InputManager::Initialize(void)
{
	m_keyboard.reset(new DirectX::Keyboard);
}

bool InputManager::IsKeyDown(Keyboard::Keys const key) const
{
	if (m_tracker.IsKeyPressed(key))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool InputManager::IsKeyUp(Keyboard::Keys const key) const
{
	if (m_tracker.IsKeyReleased(key))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool InputManager::IsKeyHeld(Keyboard::Keys const key) const
{
	if (m_keyboard->GetState().IsKeyDown(key))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void InputManager::Destroy(void)
{
	m_keyboard.release();
	m_keyboard = nullptr;
}

void InputManager::UpdateStates(void)
{
	m_tracker.Update(m_keyboard->GetState());
}