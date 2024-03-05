#pragma once
#include "GameObject.h"
class SceneGame;

class Spawner : public GameObject
{
protected:

	float interval = 1.f;
	int spawnCount = 1;
	float radius = 1000.f;

	float timer = 0.f;

	SceneGame* sceneGame;
	virtual GameObject* Create() = 0;

public:
	Spawner(const std::string& name = "");
	~Spawner() override = default;

	void Spawn();
	void Spawn(int count);

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
};

