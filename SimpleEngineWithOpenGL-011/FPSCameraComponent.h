#pragma once
#include "Actor.h"
#include "CameraComponent.h"

class FPSCameraComponent : public CameraComponent
{
public:
	FPSCameraComponent(class Actor* ownerP);

	void Update(float dt) override;

	float getPitch() const { return pitch; }
	float getPitchSpeed() const { return pitchSpeed; }
	float getMaxPitch() const { return maxPitch; }

	void SetPitchSpeed(float speed);
	void SetMaxPitch(float pitch);

private:
	float pitchSpeed;
	float maxPitch;
	float pitch;
}; 

