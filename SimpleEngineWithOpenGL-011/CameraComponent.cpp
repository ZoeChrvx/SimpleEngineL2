#include "CameraComponent.h"
#include "Game.h"

CameraComponent::CameraComponent(Actor* owner, int updateOrder) :
	Component(owner, updateOrder) {
}

void CameraComponent::SetViewMatrix(const Matrix4& view) {
	Game& game = owner.getGame();
	game.GetRenderer().SetViewMatrix(view);
}