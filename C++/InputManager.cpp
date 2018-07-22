#include "InputManager.h"

using namespace DirectX;

InputManager::InputManager(void)
	:m_keyboard(nullptr)//, m_mouse(nullptr)
{

}

InputManager::~InputManager(void)
{

}

void InputManager::Initialize(void)
{
	m_keyboard.reset(new DirectX::Keyboard);
	//m_mouse.reset(new DirectX::Mouse);
}

DirectX::Keyboard::State& InputManager::GetKeyboardState(void) const
{
	return m_keyboard->GetState();
}

/*
DirectX::Mouse::State& InputManager::GetMouseState(void) const
{
	return m_mouse->GetState();
}
*/
void InputManager::Destroy(void)
{
	m_keyboard.release();
	m_keyboard = nullptr;

	//m_mouse.release();
	//m_mouse = nullptr;
}
