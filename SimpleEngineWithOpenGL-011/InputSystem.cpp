#include "InputSystem.h"
#include <SDL_keyboard.h>
#include <cstring>

InputSystem::InputSystem() :inputState() {

}

bool InputSystem::processEvent(SDL_Event& event)
{
	bool isRunning = true;
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEWHEEL:
		inputState.mouse.scrollWheel = Vector2(
			static_cast<float>(event.wheel.x),
			static_cast<float>(event.wheel.y));
		break;
	default:
		break;
	}
	return isRunning;
}

bool InputSystem::Initialize() {
	//Keyboard
	inputState.keyboard.currentState = SDL_GetKeyboardState(nullptr);
	memset(inputState.keyboard.previousState, 0, SDL_NUM_SCANCODES);


	//Mouse 
	inputState.mouse.currentButtons = 0;
	inputState.mouse.previousButtons = 0;
	return true;
}

void InputSystem::Close() {

}

void InputSystem::PreUpdate() {
	//Keyboard
	memcpy(inputState.keyboard.previousState, inputState.keyboard.currentState, SDL_NUM_SCANCODES);

	//Mouse
	inputState.mouse.previousButtons = inputState.mouse.currentButtons;
	inputState.mouse.isRelativeMode = false;
	inputState.mouse.scrollWheel = Vector2::zero;
}

void InputSystem::Update() {
	//Mouse
	int x = 0, y = 0;
	if (inputState.mouse.isRelativeMode) {
		inputState.mouse.currentButtons = SDL_GetRelativeMouseState(&x, &y);
	}
	else {
		inputState.mouse.currentButtons = SDL_GetMouseState(&x, &y);
	}
	inputState.mouse.position.x = static_cast<float>(x);
	inputState.mouse.position.y = static_cast<float>(y);
}

void InputSystem::SetMouseCursor(bool isCursorDisplayedP) {
	isCursorDisplayed = isCursorDisplayedP;
	if (isCursorDisplayedP) {
		SDL_ShowCursor(SDL_TRUE);
	}
	else {
		SDL_ShowCursor(SDL_FALSE);
	}
}

void InputSystem::SetMouseRelativeMode(bool isMouseRelativeOnP) {
	SDL_bool set = isMouseRelativeOnP ? SDL_TRUE : SDL_FALSE;
	SDL_SetRelativeMouseMode(set);

	inputState.mouse.isRelativeMode = isMouseRelativeOnP;
}