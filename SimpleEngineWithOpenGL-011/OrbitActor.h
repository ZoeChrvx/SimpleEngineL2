#pragma once
#include "Actor.h"

class OrbitActor : public Actor
{
public:
	OrbitActor();
	void ActorInput(const InputState& inputState) override;
	void SetVisible(bool visible);

private:
	class OrbitCameraComponent* cameraComponent;
	class MeshComponent* meshComponent;
};

