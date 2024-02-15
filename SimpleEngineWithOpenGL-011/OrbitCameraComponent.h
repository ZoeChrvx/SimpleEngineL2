#pragma once
#include "CameraComponent.h"

class OrbitCameraComponent : public CameraComponent
{
public:
	OrbitCameraComponent(class Actor* owner);

	void Update(float dt) override;

	float GetPitchSpeed() const { return pitchSpeed; }
	float GetYawSpeed() const { return yawSpeed; }

	void SetPitchSpeed(float pitchSpeedP);
	void SetYawSpeed(float yaSpeedP);

private:
	Vector3 offset;

	Vector3 up;

	float pitchSpeed;
	float yawSpeed;
};

