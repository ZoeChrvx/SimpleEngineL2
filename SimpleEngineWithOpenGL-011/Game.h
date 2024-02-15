#pragma once
#include <vector>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Window.h"
#include "Vector2.h"
#include "RendererOGL.h"
#include "Camera.h"
#include "InputSystem.h"
#include "OrbitActor.h"
#include "SplineActor.h"

using std::vector;

class Game
{
public:
	static Game& instance()
	{
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

private:
	Game() : isRunning(true), isUpdatingActors(false), fps(nullptr), crosshair(nullptr), follow(nullptr), orbit(nullptr), path(nullptr) {}

public:
	bool Initialize();
	void Load();
	void Loop();
	void Unload();
	void Close();

	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);
	RendererOGL& GetRenderer() { return renderer; }

private:
	void ProcessInput();
	void Update(float dt);
	void Render();

	bool isRunning;
	Window window;
	RendererOGL renderer;

	bool isUpdatingActors;
	vector<Actor*> actors;
	vector<Actor*> pendingActors;

	void ChangeCamera(int mode);

	class FPSActor* fps;
	class SpriteComponent* crosshair;
	class FollowActor* follow;
	class OrbitActor* orbit;
	class SplineActor* path;

	InputSystem inputSystem;
};

