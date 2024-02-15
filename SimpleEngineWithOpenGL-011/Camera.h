#pragma once
#include "Actor.h"
class Camera : public Actor
{
public:
	Camera();

	void updateActor(float deltaTime);
	void actorInput(const struct InputState& inputState) override;
private:
	class MoveComponent* moveComponent;
};
