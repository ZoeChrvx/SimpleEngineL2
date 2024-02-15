#pragma once
#include "Vector2.h"
#include <SDL_stdinc.h>

class MouseState
{
	friend class InputSystem;

public:
	const Vector2& GetPosition() const { return position; }
	bool getButtonValue(int button) const;
	enum class ButtonState GetButtonState(int button)const;
	const Vector2& getScrollWheel() const { return scrollWheel; }
	bool isRelativeModeOn()const { return isRelativeMode; }

private:
	Vector2 position;
	Uint32 currentButtons;
	Uint32 previousButtons;
	Vector2 scrollWheel;
	bool isRelativeMode;
};

