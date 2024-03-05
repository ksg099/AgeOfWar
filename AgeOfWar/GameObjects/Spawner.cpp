#include "pch.h"
#include "Spawner.h"
#include "SceneGame.h"

Spawner::Spawner(const std::string& name) 
	: GameObject(name)
{
}

void Spawner::Spawn()
{
	sf::Vector2f pos = position + Utils::RandomOnUnitCircle() * radius;
	if (sceneGame != nullptr)
	{
		pos = sceneGame->ClampByTileMap(pos);
	}

	GameObject* newGo = Create();
	newGo->Init();
	newGo->Reset();
	newGo->SetPosition(pos);
	SCENE_MGR.GetCurrentScene()->AddGo(newGo);
}

void Spawner::Spawn(int count)
{
	for (int i = 0; i < count; ++i)
	{
		Spawn();
	}
}

void Spawner::Init()
{
	GameObject::Init();
}

void Spawner::Release()
{
	GameObject::Release();
}

void Spawner::Reset()
{
	GameObject::Reset();

	interval = 1.f;
	spawnCount = 1;
	radius = 500.f;

	timer = 0.f;

	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
}

void Spawner::Update(float dt)
{
	GameObject::Update(dt);

	timer += dt;
	if (timer > interval)
	{
		timer = 0.f;
		Spawn(spawnCount);
	}
}
