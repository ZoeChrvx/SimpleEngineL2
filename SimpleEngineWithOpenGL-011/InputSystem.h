#pragma once
#include "KeyboardState.h"
#include "MouseState.h"
#include <SDL_events.h>


enum class ButtonState {
	None,
	Pressed,
	Released,
	Held
};

struct InputState
{
	KeyboardState keyboard;
	MouseState mouse;
};

class InputSystem {
public:
	InputSystem();

	bool processEvent(SDL_Event& event);

	bool Initialize();
	void Close();

	const InputState getInputState() const { return inputState; }

	void PreUpdate();
	void Update();

	bool getIsCursorDisplayed() const { return isCursorDisplayed; }
	void SetMouseCursor(bool isCursorsDisplayedP);
	void SetMouseRelativeMode(bool isMouseRelativeOnP);

private:
	InputState inputState;
	bool isCursorDisplayed;
};

