#include "Game.h"
#include "Actor.h"
#include "Timer.h"
#include "Assets.h"
#include "MeshComponent.h"
#include "Cube.h"
#include "Sphere.h"
#include "Plane.h"
#include "FPSActor.h"

bool Game::Initialize()
{
	bool isWindowInit = window.Initialize();
	bool isRendererInit = renderer.Initialize(window);
	bool isInputInit = inputSystem.Initialize();
	return isWindowInit && isRendererInit && isInputInit; // Return bool && bool && bool ...to detect error
}

void Game::Load()
{
	inputSystem.SetMouseRelativeMode(true);

	Assets::LoadShader("Res\\Shaders\\Sprite.vert", "Res\\Shaders\\Sprite.frag", "", "", "", "Sprite");
	Assets::LoadShader("Res\\Shaders\\BasicMesh.vert", "Res\\Shaders\\BasicMesh.frag", "", "", "", "BasicMesh");
	Assets::LoadShader("Res\\Shaders\\Phong.vert", "Res\\Shaders\\Phong.frag", "", "", "", "Phong");

	Assets::LoadTexture(renderer, "Res\\Textures\\Default.png", "Default");
	Assets::LoadTexture(renderer, "Res\\Textures\\Cube.png", "Cube");
	Assets::LoadTexture(renderer, "Res\\Textures\\HealthBar.png", "HealthBar");
	Assets::LoadTexture(renderer, "Res\\Textures\\Plane.png", "Plane");
	Assets::LoadTexture(renderer, "Res\\Textures\\Radar.png", "Radar");
	Assets::LoadTexture(renderer, "Res\\Textures\\Sphere.png", "Sphere");
	Assets::LoadTexture(renderer, "Res\\Textures\\Crosshair.png", "Crosshair");
	Assets::LoadTexture(renderer, "Res\\Textures\\RacingCar.png", "RacingCar");
	Assets::LoadTexture(renderer, "Res\\Textures\\Rifle.png", "Rifle");
	
	Assets::LoadMesh("Res\\Meshes\\Cube.gpmesh", "Mesh_Cube");
	Assets::LoadMesh("Res\\Meshes\\Plane.gpmesh", "Mesh_Plane");
	Assets::LoadMesh("Res\\Meshes\\Sphere.gpmesh", "Mesh_Sphere");
	Assets::LoadMesh("Res\\Meshes\\Rifle.gpmesh", "Mesh_Rifle");
	Assets::LoadMesh("Res\\Meshes\\RacingCar.gpmesh", "Mesh_RacingCar");
	
	fps = new FPSActor();

	Cube* a = new Cube();
	a->SetPosition(Vector3(200.0f, 105.0f, 0.0f));
	a->SetScale(100.0f);
	Quaternion q(Vector3::unitY, -Maths::piOver2);
	q = Quaternion::Concatenate(q, Quaternion(Vector3::unitZ, Maths::pi + Maths::pi / 4.0f));
	a->SetRotation(q);
	
	Sphere* b = new Sphere();
	b->SetPosition(Vector3(200.0f, -75.0f, 0.0f));
	b->SetScale(3.0f);

	// Floor and walls

	// Setup floor
	const float start = -1250.0f;
	const float size = 250.0f;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Plane* p = new Plane();
			p->SetPosition(Vector3(start + i * size, start + j * size, -100.0f));
		}
	}

	// Left/right walls
	q = Quaternion(Vector3::unitX, Maths::piOver2);
	for (int i = 0; i < 10; i++)
	{
		Plane* p = new Plane();
		p->SetPosition(Vector3(start + i * size, start - size, 0.0f));
		p->SetRotation(q);

		p = new Plane();
		p->SetPosition(Vector3(start + i * size, -start + size, 0.0f));
		p->SetRotation(q);
	}

	q = Quaternion::Concatenate(q, Quaternion(Vector3::unitZ, Maths::piOver2));
	
	// Forward/back walls
	for (int i = 0; i < 10; i++)
	{
		Plane* p = new Plane();
		p->SetPosition(Vector3(start - size, start + i * size, 0.0f));
		p->SetRotation(q);

		p = new Plane();
		p->SetPosition(Vector3(-start + size, start + i * size, 0.0f));
		p->SetRotation(q);
	}

	// Setup lights
	renderer.SetAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	DirectionalLight& dir = renderer.GetDirectionalLight();
	dir.direction = Vector3(0.0f, -0.707f, -0.707f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	//Crosshair
	Actor* crosshairActor = new Actor();
	crosshairActor->SetScale(2.0f);
	crosshair = new SpriteComponent(crosshairActor, Assets::GetTexture("CrossHair"));
}

void Game::ProcessInput()
{
	inputSystem.PreUpdate();

	// SDL Event
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}

	inputSystem.Update();
	const InputState& input = inputSystem.getInputState();

	// Escape: quit game
	if (input.keyboard.GetKeyState(SDL_SCANCODE_ESCAPE)==ButtonState::Released)
	{
		isRunning = false;
	}
	// Actor input
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->ProcessInput(input);
	}
	isUpdatingActors = false;
}

void Game::Update(float dt)
{
	// Update actors 
	isUpdatingActors = true;
	for(auto actor: actors) 
	{
		actor->Update(dt);
	}
	isUpdatingActors = false;

	// Move pending actors to actors
	for (auto pendingActor: pendingActors)
	{
		pendingActor->ComputeWorldTransform();
		actors.emplace_back(pendingActor);
	}
	pendingActors.clear();

	// Delete dead actors
	vector<Actor*> deadActors;
	for (auto actor : actors)
	{
		if (actor->getState() == Actor::ActorState::Dead)
		{
			deadActors.emplace_back(actor);
		}
	}
	for (auto deadActor : deadActors)
	{
		delete deadActor;
	}
}

void Game::Render()
{
	renderer.BeginDraw();
	renderer.Draw();
	renderer.EndDraw();
}

void Game::Loop()
{
	Timer timer;
	float dt = 0;
	while (isRunning)
	{
		float dt = timer.computeDeltaTime() / 1000.0f;
		ProcessInput();
		Update(dt);
		Render();
		timer.delayTime();
	}
}

void Game::Unload()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!actors.empty())
	{
		delete actors.back();
	}

	// Resources
	Assets::clear();
}

void Game::Close()
{
	inputSystem.Close();
	renderer.Close();
	window.close();
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	if (isUpdatingActors)
	{
		pendingActors.emplace_back(actor);
	}
	else
	{
		actors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	// Erase actor from the two vectors
	auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
	if (iter != end(pendingActors))
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, end(pendingActors) - 1);
		pendingActors.pop_back();
	}
	iter = std::find(begin(actors), end(actors), actor);
	if (iter != end(actors))
	{
		std::iter_swap(iter, end(actors) - 1);
		actors.pop_back();
	}
}