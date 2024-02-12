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
	FPSModel->setScale(0.75f);
	meshComponent = new MeshComponent(FPSModel);
	meshComponent->setMesh(Assets::getMesh("Mesh_Rifle"));
}

void FPSActor::UpdateActor(float dt) {
	Actor::updateActor(dt);

	Vector3 modelPosition = getPosition();
	modelPosition += getForward() * MODEL_OFFSET.x;
	modelPosition += getRight() * MODEL_OFFSET.y;
	modelPosition.z += MODEL_OFFSET.z;
	FPSModel->setPosition(modelPosition);
	Quaternion q = getRotation();
	q = Quaternion::concatenate(q, Quaternion(getRight(), cameraComponent->getPitch()));
	FPSModel->setRotation(q);
}