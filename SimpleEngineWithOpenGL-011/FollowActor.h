#pragma once
#include "Actor.h"

class FollowActor : public Actor
{
public:
	FollowActor();

	void ActorInput(const InputState& inputSTate) override;
	void SetVisible(bool isVisibleP);

private:
	class MoveComponent* moveComponent;
	class FollowCameraComponent* cameraComponent;
	class MeshComponent* meshComponent;
};

