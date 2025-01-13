#include "MoveComponent.h"
#include "Maths.h"
#include "Actor.h"
#include "Window.h"

MoveComponent::MoveComponent(Actor* ownerP, int updateOrderP)
	: Component(ownerP, updateOrderP), forwardSpeed(0.0f), angularSpeed(0.0f), strafeSpeed(0.0f)
{

}

void MoveComponent::setForwardSpeed(float forwardSpeedP)
{
	forwardSpeed = forwardSpeedP;
}

void MoveComponent::setAngularSpeed(float angularSpeedP)
{
	angularSpeed = angularSpeedP;
}

void MoveComponent::setStrafeSpeed(float strafeSpeedP)
{
	strafeSpeed = strafeSpeedP;
}

void MoveComponent::setVerticalSpeed(float verticalSpeedP)
{
	verticalSpeed = verticalSpeedP;
}

void MoveComponent::setRollSpeed(float rollSpeedP)
{
	rollSpeed = rollSpeedP;
}

void MoveComponent::setYawSpeed(float yawSpeedP)
{
	yawSpeed = yawSpeedP;
}

void MoveComponent::setPitchSpeed(float pitchSpeedP)
{
	pitchSpeed = pitchSpeedP;
}

void MoveComponent::update(float dt)
{
	if (!Maths::nearZero(angularSpeed))
	{
		Quaternion newRotation = owner.getRotation();
		float angle = angularSpeed * dt;
		Quaternion increment(Vector3::unitZ, angle);
		newRotation = Quaternion::concatenate(newRotation, increment);
		owner.setRotation(newRotation);
	}
	if (!Maths::nearZero(rollSpeed))
	{
		Quaternion newRotation = owner.getRotation();
		float angle = rollSpeed * dt;
		Quaternion increment(Vector3::unitX, angle);
		newRotation = Quaternion::concatenate(newRotation, increment);
		owner.setRotation(newRotation);
	}
	if (!Maths::nearZero(yawSpeed))
	{
		Quaternion newRotation = owner.getRotation();
		float angle = yawSpeed * dt;
		Quaternion increment(Vector3::unitZ, angle);
		newRotation = Quaternion::concatenate(newRotation, increment);
		owner.setRotation(newRotation);
	}
	if (!Maths::nearZero(pitchSpeed))
	{
		Quaternion newRotation = owner.getRotation();
		float angle = pitchSpeed * dt;
		Quaternion increment(Vector3::unitY, angle);
		newRotation = Quaternion::concatenate(newRotation, increment);
		owner.setRotation(newRotation);
	}
	if (!Maths::nearZero(forwardSpeed) || !Maths::nearZero(strafeSpeed))
	{
		Vector3 newPosition = owner.getPosition();
		newPosition += owner.getForward() * forwardSpeed * dt;
		newPosition += owner.getRight() * strafeSpeed * dt;
		owner.setPosition(newPosition);
	}
	if (!Maths::nearZero(verticalSpeed))
	{
		Vector3 newPosition = owner.getPosition();
		newPosition += owner.getUp() * verticalSpeed * dt;
		owner.setPosition(newPosition);
	}
	
}
