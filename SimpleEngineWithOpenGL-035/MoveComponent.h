#pragma once
#include "Component.h"
class MoveComponent : public Component
{
public:
	MoveComponent(Actor* ownerP, int updateOrder = 10); // By default, update before other components
	MoveComponent() = delete;
	MoveComponent(const MoveComponent&) = delete;
	MoveComponent& operator=(const MoveComponent&) = delete;

	float getForwardSpeed() const { return forwardSpeed; }
	float getAngularSpeed() const { return angularSpeed; }
	float getStrafeSpeed() const { return strafeSpeed; }
	float getVerticalSpeed() const { return verticalSpeed; }
	float getRollSpeed() const { return rollSpeed; }
	float getYawSpeed() const { return yawSpeed; }
	float getPitchSpeed() const { return pitchSpeed; }

	void setForwardSpeed(float forwardSpeedP);
	void setAngularSpeed(float angularSpeedP);
	void setStrafeSpeed(float strafeSpeedP);
	void setVerticalSpeed(float verticalSpeedP);
	void setRollSpeed(float rollSpeedP);
	void setYawSpeed(float yawSpeedP);
	void setPitchSpeed(float pitchSpeedP);

	void update(float dt) override;


private:
	float forwardSpeed;
	float strafeSpeed;
	float verticalSpeed;
	float angularSpeed;
	float rollSpeed;
	float yawSpeed;
	float pitchSpeed;
};

