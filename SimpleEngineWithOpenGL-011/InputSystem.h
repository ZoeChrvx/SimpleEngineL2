#pragma once
#include "KeyboardState.h"
#include "MouseState.h"
#include "ControllerState.h"
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
	ControllerState controller;
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

	bool GetIsCursorDisplayed() const { return isCursorDisplayed; }
	void SetMouseCursor(bool isCursorsDisplayedP);
	void SetMouseRelativeMode(bool isMouseRelativeOnP);

private:
	float filter1D(int input);
	Vector2 filter2D(int inputX, int inputY);

	InputState inputState;
	bool isCursorDisplayed;

	SDL_GameController* controller;
};

constexpr int CONTROLLER_DEAD_ZONE_1D = 250;
constexpr float CONTROLLER_DEAD_ZONE_2D = 8000.0f;
constexpr int CONTROLLER_MAX_VALUE = 30000;
