#include "SplineActor.h"
#include "SplineCameraComponent.h"

SplineActor::SplineActor(): Actor(), cameraComponent(nullptr)
{
	cameraComponent = new SplineCameraComponent(this);

	Spline spline;
	spline.controlPoints.emplace_back(Vector3::zero);
	for (int i = 0; i < 5; i++) {
		if (i % 2 == 0) {
			spline.controlPoints.emplace_back(Vector3(300.0f * (i + 1), 300.0f, 300.0f));
		}
		else {
			spline.controlPoints.emplace_back(Vector3(300.0f * (i + 1), 0.0f, 0.0f));
		}
	}

	cameraComponent->SetSpline(spline);
	cameraComponent->SetPaused(false);
}

void SplineActor::ActorInput(const InputState& inputState)
{
}

void SplineActor::RestartSpline()
{
	cameraComponent->Restart();
}
