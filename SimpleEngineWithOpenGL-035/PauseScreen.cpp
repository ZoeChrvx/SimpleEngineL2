#include "PauseScreen.h"
#include "Game.h"

PauseScreen::PauseScreen()
{
	Game::instance().setState(GameState::Pause);
	setTitle("PauseTitle");
}

PauseScreen::~PauseScreen()
{
	Game::instance().setState(GameState::Gameplay);
}

void PauseScreen::processInput(const InputSTate& inputState)
{
	UIScreen::processInput(inputState);
	if(inputState.keyboard.getKeyState(SDL_SCANCODE_ESCAPE)==ButtonState::Released)
	{
		close();
	}
}
