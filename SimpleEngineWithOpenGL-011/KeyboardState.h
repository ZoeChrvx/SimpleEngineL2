#pragma once
#include <SDL_keyboard.h>

class KeyboardState
{
	friend class InputSystem;

public: bool GetKeyValue(SDL_Scancode key) const;
	  enum class ButtonState GetKeyState(SDL_Scancode key)const;

private:
	const Uint8* currentState;
	Uint8 previousState[SDL_NUM_SCANCODES];
};

