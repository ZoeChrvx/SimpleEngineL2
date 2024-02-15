#include "Plane.h"
#include "MeshComponent.h"
#include "Assets.h"

Plane::Plane() : Actor()
{
	SetScale(10.0f);
	MeshComponent* mc = new MeshComponent(this);
	mc->SetMesh(Assets::getMesh("Mesh_Plane"));
}
