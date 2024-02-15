#pragma once
#include "Actor.h"
class Camera : public Actor
{
public:
	Camera();

	void UpdateActor(float deltaTime);
	void ActorInput(const struct InputState& inputState) override;
private:
	class MoveComponent* moveComponent;
};
