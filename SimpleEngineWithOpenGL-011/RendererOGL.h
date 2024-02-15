#pragma once
#include "IRenderer.h"
#include "VertexArray.h"
#include "Vector2.h"
#include "Shader.h"

#include <vector>
#include "DirectionalLight.h"

class RendererOGL : public IRenderer
{
public:
	RendererOGL();
	virtual ~RendererOGL();
	RendererOGL(const RendererOGL&) = delete;
	RendererOGL& operator=(const RendererOGL&) = delete;

	bool Initialize(Window& window);
	void BeginDraw();
	void Draw();
	void EndDraw();
	void Close();
	IRenderer::Type type() { return Type::OGL; }

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	void DrawSprite(const Actor& actor, const class Texture& tex, struct Rectangle srcRect, Vector2 origin, Flip flip) const;

	void AddMesh(class MeshComponent* mesh);
	void RemoveMesh(class MeshComponent* mesh);

	DirectionalLight& GetDirectionalLight() { return dirLight; }

	void SetViewMatrix(const Matrix4& viewP);
	void SetLightUniforms(Shader& shader);
	void SetAmbientLight(const Vector3& ambientP);

private:
	void DrawMeshes();
	void DrawSprites();

	Window* window;
	SDL_GLContext context;
	VertexArray* spriteVertexArray;
	Matrix4 spriteViewProj;
	Matrix4 view;
	Matrix4 projection;

	std::vector<class MeshComponent*> meshes;
	std::vector<class SpriteComponent*> sprites;

	Vector3 ambientLight;
	DirectionalLight dirLight;
};

