#include "FollowCameraComponent.h"
#include "Actor.h"

FollowCameraComponent::FollowCameraComponent(Actor* ownerP) :
	CameraComponent(ownerP),
	horizontalDistance(FOLLOW_HORIZONTAL_DISTANCE),
	verticalDistance(FOLLOW_VERTICAL_DISTANCE),
	targetDistance(FOLLOW_TARGET_DISTANCE),
	springConstant(FOLLOW_SPRING_CONSTANT)
{
}

void FollowCameraComponent::Update(float dt)
{
	CameraComponent::Update(dt);

	float dampening = 2.0f * Maths::sqrt(springConstant);
	Vector3 idealPosition = computeCameraPosition();
	Vector3 diff = actualPosition - idealPosition;
	Vector3 accel = -springConstant * diff - dampening * velocity;
	velocity += accel * dt;
	actualPosition += velocity * dt;

	Vector3 target = owner.getPosition() + owner.getForward() * targetDistance;
	Matrix4 view = Matrix4::createLookAt(actualPosition, target, Vector3::unitZ);
	SetViewMatrix(view);
}

void FollowCameraComponent::SnapToIdeal()
{
	actualPosition = computeCameraPosition();
	velocity = Vector3::zero;
	Vector3 target = owner.getPosition() + owner.getForward() * targetDistance;
	Matrix4 view = Matrix4::createLookAt(actualPosition, target, Vector3::unitZ);
	SetViewMatrix(view);
}

void FollowCameraComponent::SetHorizontalDistance(float distance)
{
	horizontalDistance = distance;
}

void FollowCameraComponent::SetVerticalDistance(float distance)
{
	verticalDistance = distance;
}

void FollowCameraComponent::SetTargetDistance(float distance)
{
	targetDistance = distance;
}

void FollowCameraComponent::SetSpringConstant(float springConstantP)
{
	springConstant = springConstantP;
}

Vector3 FollowCameraComponent::computeCameraPosition() const
{
	Vector3 cameraPosition = owner.getPosition();
	cameraPosition -= owner.getPosition();
	cameraPosition += Vector3::unitZ * verticalDistance;
	return cameraPosition;
}
