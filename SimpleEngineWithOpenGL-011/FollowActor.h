#pragma once
#include "Actor.h"

class FollowActor : public Actor
{
public:
	FollowActor();

	void ActorInput(const InputState& inputState) override;
	void SetVisible(bool isVisibleP);

private:
	class MoveComponent* moveComponent;
	class FollowCameraComponent* cameraComponent;
	class MeshComponent* meshComponent;
};

