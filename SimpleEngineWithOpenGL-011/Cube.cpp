#include "Cube.h"
#include "MeshComponent.h"
#include "Assets.h"

Cube::Cube()
{
	MeshComponent* mc = new MeshComponent(this);
	mc->SetMesh(Assets::getMesh("Mesh_Cube"));
}
