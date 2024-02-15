#include "SplineCameraComponent.h"

SplineCameraComponent::SplineCameraComponent(Actor* ownerP) :
	CameraComponent(ownerP),
	index(1),
	t(0.0f),
	speed(0.5f),
	isPaused(true) 
{
}

void SplineCameraComponent::Update(float dt)
{
	CameraComponent::Update(dt);

	if (!isPaused) {
		t += speed * dt;

		if (t >= 1.0f) {
			if (index < spline.getNbPoints() - 3) {
				index++;
				t = t - 1.0f;
			}
			else {
				isPaused = true;
			}
		}
	}

	Vector3 cameraPosition = spline.Compute(index, t);
	Vector3 target = spline.Compute(index, t + 0.01f);
	Matrix4 view = Matrix4::createLookAt(cameraPosition, target, Vector3::unitZ);
	SetViewMatrix(view);
}

void SplineCameraComponent::SetSpeed(float speedP)
{
	speed = speedP;
}

void SplineCameraComponent::SetSpline(const Spline& splineP)
{
	spline = splineP;
}

void SplineCameraComponent::SetPaused(bool isPausesP)
{
	isPaused = isPausesP;
}

void SplineCameraComponent::Restart()
{
	index = 1;
	t = 0.0f;
	isPaused = false;
}

