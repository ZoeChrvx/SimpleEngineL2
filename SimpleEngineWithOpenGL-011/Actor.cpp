#include "Actor.h"
#include <algorithm>
#include "Game.h"
#include "Component.h"
#include "Maths.h"

Actor::Actor() :
	state(Actor::ActorState::Active),
	position(Vector3::zero),
	scale(1.0f),
	rotation(Quaternion::identity),
	mustRecomputeWorldTransform(true),
	game(Game::instance())
{
	game.AddActor(this);
}

Actor::~Actor()
{
	game.RemoveActor(this);
	// Need to delete components
	// Because ~Component calls RemoveComponent, need a different style loop
	while (!components.empty())
	{
		delete components.back();
	}
}

void Actor::SetPosition(Vector3 positionP)
{
	position = positionP;
	mustRecomputeWorldTransform = true;
}

void Actor::SetScale(float scaleP)
{
	scale = scaleP;
	mustRecomputeWorldTransform = true;
}

void Actor::SetRotation(Quaternion rotationP)
{
	rotation = rotationP;
	mustRecomputeWorldTransform = true;
}

void Actor::SetState(ActorState stateP)
{
	state = stateP;
}

Vector3 Actor::getForward() const
{
	return Vector3::transform(Vector3::unitX, rotation);
}

void Actor::ComputeWorldTransform()
{
	if (mustRecomputeWorldTransform)
	{
		mustRecomputeWorldTransform = false;
		worldTransform = Matrix4::createScale(scale);
		worldTransform *= Matrix4::createFromQuaternion(rotation);
		worldTransform *= Matrix4::createTranslation(position);

		for (auto component : components)
		{
			component->OnUpdateWorldTransform();
		}
	}
}

void Actor::ProcessInput(const struct InputState& inputState)
{
	if (state == Actor::ActorState::Active)
	{
		for (auto component : components)
		{
			component->ProcessInput(inputState);
		}
		ActorInput(inputState);
	}
}

void Actor::ActorInput(const struct InputState& inputState)
{
}

void Actor::Update(float dt)
{
	if (state == Actor::ActorState::Active)
	{
		ComputeWorldTransform();
		updateComponents(dt);
		updateActor(dt);
		ComputeWorldTransform();
	}
}

void Actor::updateComponents(float dt)
{
	for (auto component : components)
	{
		component->Update(dt);
	}
}

void Actor::updateActor(float dt)
{
}

void Actor::addComponent(Component* component)
{
	// Find the insertion point in the sorted vector
	// (The first element with a order higher than me)
	int myOrder = component->GetUpdateOrder();
	auto iter = begin(components);
	for (; iter != end(components); ++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	components.insert(iter, component);
}

void Actor::removeComponent(Component* component)
{
	auto iter = std::find(begin(components), end(components), component);
	if (iter != end(components))
	{
		components.erase(iter);
	}
}

Vector3 Actor::getRight()const {
	return Vector3::transform(Vector3::unitY, rotation);
}
