#include "FollowActor.h"
#include "MoveComponent.h"
#include "FollowCameraComponent.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "InputSystem.h"

FollowActor::FollowActor() :
	Actor(),
	moveComponent(nullptr),
	cameraComponent(nullptr),
	meshComponent(nullptr)
{
	meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(Assets::getMesh("Mesh_RacingCar"));
	SetPosition(Vector3(0.0f, 0.0f, -100.0f));

	moveComponent = new MoveComponent(this);
	cameraComponent = new FollowCameraComponent(this);
	cameraComponent->SnapToIdeal();
}

void FollowActor::ActorInput(const InputState& inputState)
{
	float forwardSpeed = 0.0f;
	float angularSpeed = 
}

void FollowActor::SetVisible(bool isVisibleP)
{
}
