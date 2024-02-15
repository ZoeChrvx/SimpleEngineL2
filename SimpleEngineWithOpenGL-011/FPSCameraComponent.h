#pragma once
#include "Actor.h"
#include "CameraComponent.h"

class FPSCameraComponent : public CameraComponent
{
public:
	FPSCameraComponent(class Actor* ownerP);

	void Update(float dt) override;

	float GetPitch() const { return pitch; }
	float GetPitchSpeed() const { return pitchSpeed; }
	float GetMaxPitch() const { return maxPitch; }

	void SetPitchSpeed(float speed);
	void SetMaxPitch(float pitch);

private:
	float pitchSpeed;
	float maxPitch;
	float pitch;
}; 

