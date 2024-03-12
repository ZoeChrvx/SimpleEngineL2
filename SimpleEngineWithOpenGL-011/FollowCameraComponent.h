#pragma once
#include "CameraComponent.h"
class FollowCameraComponent : public CameraComponent
{
public:
	FollowCameraComponent(class Actor* ownerP);

	void update(float dt) override;
	void snapToIdeal();

	void setHorizontalDistance(float distance);
	void setVerticalDistance(float distance);
	void setTargetDistance(float distance);
	void setSpringConstant(float springConstantP);


private:
	Vector3 computeCameraPosition() const;

	Vector3 actualPosition;
	Vector3 velocity;
	float horizontalDistance;
	float verticalDistance;
	float targetDistance;
	float springConstant;
};

constexpr float FOLLOW_HORIZONTAL_DISTANCE = 1800.0f;
constexpr float FOLLOW_VERTICAL_DISTANCE = 3000.0f;
constexpr float FOLLOW_TARGET_DISTANCE = 550.0f;
constexpr float FOLLOW_SPRING_CONSTANT = 800.0f;