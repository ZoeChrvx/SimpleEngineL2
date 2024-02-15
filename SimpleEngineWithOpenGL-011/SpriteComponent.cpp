#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Rectangle.h"

SpriteComponent::SpriteComponent(Actor* ownerP, Texture& textureP, int drawOrderP):
	Component(ownerP),
	texture(textureP), 
	drawOrder(drawOrderP), 
	texWidth(textureP.getWidth()),
	texHeight(textureP.getHeight()),
	isVisible(true)
{
	owner.getGame().GetRenderer().AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	owner.getGame().GetRenderer().RemoveSprite(this);
}

void SpriteComponent::setTexture(const Texture& textureP)
{
	texture = textureP;
	texture.updateInfo(texWidth, texHeight);
}

void SpriteComponent::draw(IRenderer& renderer)
{
	Vector2 origin{ texWidth / 2.f, texHeight / 2.f };
	renderer.DrawSprite(owner, texture,	Rectangle::nullRect, origin, IRenderer::Flip::None);
}

void SpriteComponent::SetVisible(bool isVisibleP)
{
	isVisible = isVisibleP;
}

