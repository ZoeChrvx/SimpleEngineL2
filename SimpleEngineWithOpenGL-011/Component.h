#pragma once
#include <SDL_stdinc.h>

class Actor;

class Component
{
public:
	Component(Actor* ownerP, int updateOrderP = 100);
	Component() = delete;
	virtual ~Component();
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;

	int GetUpdateOrder() const { return updateOrder; }

	virtual void ProcessInput(const struct InputState& inputState);
	virtual void Update(float dt);
	virtual void OnUpdateWorldTransform() {}

protected:
	Actor& owner;
	int updateOrder;		// Order of the component in the actor's updateComponent method
};

