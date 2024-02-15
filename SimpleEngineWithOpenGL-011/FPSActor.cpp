#include "FPSActor.h"
#include "MoveComponent.h"
#include "Game.h"
#include "FPSCameraComponent.h"
#include "MeshComponent.h"
#include "Assets.h"

FPSActor::FPSActor() :
	Actor(),
	moveComponent(nullptr),
	meshComponent(nullptr),
	cameraComponent(nullptr) 
{
	moveComponent = new MoveComponent(this);
	cameraComponent = new FPSCameraComponent(this);

	FPSModel = new Actor();
	FPSModel->SetScale(0.75f);
	meshComponent = new MeshComponent(FPSModel);
	meshComponent->SetMesh(Assets::getMesh("Mesh_Rifle"));
}

void FPSActor::UpdateActor(float dt) {
	Actor::updateActor(dt);

	Vector3 modelPosition = getPosition();
	modelPosition += getForward() * MODEL_OFFSET.x;
	modelPosition += getRight() * MODEL_OFFSET.y;
	modelPosition.z += MODEL_OFFSET.z;
	FPSModel->SetPosition(modelPosition);
	Quaternion q = getRotation();
	q = Quaternion::Concatenate(q, Quaternion(getRight(), cameraComponent->GetPitch()));
	FPSModel->SetRotation(q);
}

void FPSActor::ActorInput(const InputState& inputState) {
	float forwardSpeed = 0.0f;
	float strafeSpeed = 0.0f;

	//WASD Move
	if (inputState.keyboard.GetKeyValue(SDL_SCANCODE_W)) {
		forwardSpeed += 400.f;
	}
	if (inputState.keyboard.GetKeyValue(SDL_SCANCODE_S)) {
		forwardSpeed -= 400.f;
	}
	if (inputState.keyboard.GetKeyValue(SDL_SCANCODE_A)) {
		strafeSpeed -= 400.f;
	}
	if (inputState.keyboard.GetKeyValue(SDL_SCANCODE_D)) {
		strafeSpeed += 400.f;
	}
	moveComponent->SetForwardSpeed(forwardSpeed);
	moveComponent->SetStrafeSpeed(strafeSpeed);

	//Mouse Move
	Vector2 mousePosition = inputState.mouse.GetPosition();
	float x = mousePosition.x;
	float y = mousePosition.y;
	const int maxMouseSpeed = 500;
	const float maxAngularSpeed = Maths::pi * 8;
	float angularSpeed = 0.0f;
	if (x != 0) {
		angularSpeed = x / maxMouseSpeed;
		angularSpeed *= maxAngularSpeed;
	}
	moveComponent->SetAngularSpeed(angularSpeed);
	const float maxPitchSpeed = Maths::pi * 8;
	float pitchSpeed = 0.0f;
	if (y != 0) {
		pitchSpeed = y / maxMouseSpeed;
		pitchSpeed *= maxPitchSpeed;
	}
	cameraComponent->SetPitchSpeed(pitchSpeed);
}

void FPSActor::SetVisible(bool isVisible) {
	meshComponent->SetVisible(isVisible);
}