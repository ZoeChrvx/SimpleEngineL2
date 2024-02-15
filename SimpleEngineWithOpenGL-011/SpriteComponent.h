#pragma once
#include "Component.h"
#include "Texture.h"

class SpriteComponent :	public Component
{
public:
	SpriteComponent(Actor* ownerP, Texture& textureP, int drawOrderP = 100); // Lower draw order: further back
	virtual ~SpriteComponent();
	SpriteComponent() = delete;
	SpriteComponent(const SpriteComponent&) = delete;
	SpriteComponent& operator=(const SpriteComponent&) = delete;

	virtual void setTexture(const Texture& textureP);
	virtual void draw(IRenderer& renderer);

	int GetDrawOrder() const { return drawOrder; }
	int GetTexWidth() const { return texWidth; }
	int GetTexHeight() const { return texHeight; }
	int GetVisible() const { return isVisible; }

	void SetVisible(bool isVisibleP);

protected:
	Texture texture;
	int drawOrder;
	int texWidth;
	int texHeight;
	bool isVisible;
};

