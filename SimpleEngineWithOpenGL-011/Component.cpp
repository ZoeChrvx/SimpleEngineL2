#include "Component.h"
#include "Actor.h"

Component::Component(Actor* ownerP, int updateOrderP):
	owner(*ownerP),
	updateOrder(updateOrderP)
{
	owner.addComponent(this);
}

Component::~Component()
{
	owner.removeComponent(this);
}

void Component::ProcessInput(const struct InputState& inputState)
{
}

void Component::Update(float dt)
{
}
