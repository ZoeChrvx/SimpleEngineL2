#include "MeshComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Mesh.h"

MeshComponent::MeshComponent(Actor* owner) : Component(owner), mesh(nullptr), textureIndex(0), isVisible(true)
{
	owner->getGame().GetRenderer().AddMesh(this);
}

MeshComponent::~MeshComponent()
{
	owner.getGame().GetRenderer().RemoveMesh(this);
}

void MeshComponent::Draw(Shader& shader)
{
	if (mesh)
	{
		Matrix4 wt = owner.getWorldTransform();
		shader.setMatrix4("uWorldTransform", wt);
		shader.setFloat("uSpecPower", mesh->getSpecularPower());
		Texture* t = mesh->GetTexture(textureIndex);
		if (t)
		{
			t->setActive();
		}
		VertexArray* va = mesh->getVertexArray();
		va->setActive();
		glDrawElements(GL_TRIANGLES, va->getNbIndices(), GL_UNSIGNED_INT, nullptr);
	}
}

void MeshComponent::SetMesh(Mesh& meshP)
{
	mesh = &meshP;
}

void MeshComponent::SetTextureIndex(size_t textureIndexP)
{
	textureIndex = textureIndexP;
}

void MeshComponent::SetVisible(bool isVisibleP)
{
	isVisible = isVisibleP;
}
