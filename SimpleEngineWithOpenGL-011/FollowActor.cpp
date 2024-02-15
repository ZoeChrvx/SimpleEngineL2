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
	float angularSpeed = 0.0f;

	//WASD Move
	if (inputState.keyboard.GetKeyValue(SDL_SCANCODE_W)) {
		forwardSpeed += 400.0f;
	}
	if (inputState.keyboard.GetKeyValue(SDL_SCANCODE_S)) {
		forwardSpeed -= 400.0f;
	}
	if (inputState.keyboard.GetKeyValue(SDL_SCANCODE_A)) {
		angularSpeed -= Maths::pi;
	}
	if (inputState.keyboard.GetKeyValue(SDL_SCANCODE_D)) {
		angularSpeed += Maths::pi;
	}

	moveComponent->SetForwardSpeed(forwardSpeed);
	moveComponent->SetAngularSpeed(angularSpeed);

	if (!Maths::nearZero(forwardSpeed)) {
		cameraComponent->SetHorizontalDistance(500.0f);
	}
	else {
		cameraComponent->SetHorizontalDistance(350.0f);
	}
}

void FollowActor::SetVisible(bool isVisibleP)
{
	meshComponent->SetVisible(isVisibleP);
}
