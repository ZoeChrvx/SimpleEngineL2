#pragma once
#include "Component.h"
class MeshComponent : public Component
{
public:
	MeshComponent(Actor* owner);
	virtual ~MeshComponent();

	virtual void Draw(class Shader& shader);
	virtual void SetMesh(class Mesh& meshP);
	void SetTextureIndex(size_t textureIndexP);

	bool GetVisible() const { return isVisible; }
	void SetVisible(bool isVisibleP);

protected:
	Mesh* mesh;
	size_t textureIndex;
	bool isVisible;
};

