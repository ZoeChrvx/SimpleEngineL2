#pragma once
#include "Actor.h"

class SplineActor : public Actor
{
public:
	SplineActor();

	void ActorInput(const InputState& inputState) override;
	void RestartSpline();

private:
	class SplineCameraComponent* cameraComponent;
};

