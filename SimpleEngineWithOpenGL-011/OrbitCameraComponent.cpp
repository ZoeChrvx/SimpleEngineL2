#include "OrbitCameraComponent.h"
#include "Actor.h"

OrbitCameraComponent::OrbitCameraComponent(Actor* ownerP) :
	CameraComponent(ownerP),
	offset(-400.0f, 0.0f, 0.0f),
	up(Vector3::unitZ),
	pitchSpeed(0.0f),
	yawSpeed(0.0f)
{
}

void OrbitCameraComponent::Update(float dt)
{
	CameraComponent::Update(dt);

	Quaternion yaw{ Vector3::unitZ,yawSpeed * dt };
	offset = Vector3::transform(offset, yaw);
	up = Vector3::transform(up, yaw);

	Vector3 forward = -1.0f * offset;
	forward.Normalize();
	Vector3 right = Vector3::cross(up, forward);
	right.Normalize();

	Quaternion pitch{ right, pitchSpeed * dt };
	offset = Vector3::transform(offset, pitch);
	up = Vector3::transform(up, pitch);

	Vector3 target = owner.getPosition();
	Vector3 cameraPosition = target + offset;
	Matrix4 view = Matrix4::createLookAt(cameraPosition, target, up);
	SetViewMatrix(view);
}

void OrbitCameraComponent::SetPitchSpeed(float pitchSpeedP)
{
	pitchSpeed = pitchSpeedP;
}

void OrbitCameraComponent::SetYawSpeed(float yawSpeedP)
{
	yawSpeed = yawSpeedP;
}
