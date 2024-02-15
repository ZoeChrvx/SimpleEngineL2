#pragma once
#include "CameraComponent.h"
#include "Spline.h"

class SplineCameraComponent : public CameraComponent
{
public:
	SplineCameraComponent(class Actor* ownerP);

	void Update(float dt) override;

	void SetSpeed(float speedP);
	void SetSpline(const Spline& splineP);
	void SetPaused(bool isPausesP);

	void Restart();

private:
	Spline spline;
	size_t index;
	float t;
	float speed;
	bool isPaused;
};

