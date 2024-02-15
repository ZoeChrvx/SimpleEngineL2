#include "Sphere.h"
#include "MeshComponent.h"
#include "Assets.h"

Sphere::Sphere() : Actor()
{
	MeshComponent* mc = new MeshComponent(this);
	mc->SetMesh(Assets::getMesh("Mesh_Sphere"));
}
