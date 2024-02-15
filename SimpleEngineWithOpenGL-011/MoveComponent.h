#pragma once
#include "Component.h"
class MoveComponent : public Component
{
public:
	MoveComponent(Actor* ownerP, int updateOrder = 10); // By default, update before other components
	MoveComponent() = delete;
	MoveComponent(const MoveComponent&) = delete;
	MoveComponent& operator=(const MoveComponent&) = delete;

	float GetForwardSpeed() const { return forwardSpeed; }
	float GetAngularSpeed() const { return angularSpeed; }
	float GetStrafeSpeed() const { return strafeSpeed; }

	void SetForwardSpeed(float forwardSpeedP);
	void SetAngularSpeed(float angularSpeedP);
	void SetStrafeSpeed(float strafeSpeedP);

	void Update(float dt) override;


private:
	float forwardSpeed;
	float angularSpeed;
	float strafeSpeed;

};

