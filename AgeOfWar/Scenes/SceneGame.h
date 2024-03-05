#pragma once
#include "Scene.h"
#include <fstream>
#include <iostream>
#include "TextGo.h"

class Player;
class Spawner;
class TileMap;
class Zombie;
class UiHud;
class SpriteGo;
class Upgrade;
class ItemSpawner;
class TextGo;
class UpGrade;

class SceneGame : public Scene
{
public:
	enum class Status
	{
		Title,
		Playing,
		NextWave,
		GameOver,
		Pause,
	};
protected:
	Status currentStatus;

	Player* player = nullptr;
	TileMap* tileMap;

	std::vector<Spawner*> zspawners;
	std::vector<Spawner*> ispawners;

	std::list<GameObject*> zombieList;

	UiHud* hud;
	SpriteGo* crosshair;
	Upgrade* upui;
	ItemSpawner* value;
	TextGo* uiText;
	TextGo* uiMsg;
	TextGo* restartMsg;
	TextGo* exitMsg;
	TextGo* pause;

	bool upUiScene = true;
	
	int wave = 1;
	int Score = 0;
	int HiScore = 0;
	
	
	float timer = 0.f;
	int fpsCount = 0;
	int fps = 0.f;

public:
	SceneGame(SceneIds id);
	~SceneGame() override = default;

	const std::list<GameObject*>& GetZombieList() const { return zombieList; }

	UiHud* GetHud() const
	{
		return hud;
	}

	Status GetStatus() const { return currentStatus; }
	void SetStatus(Status newStatus);

	bool IsInTileMap(const sf::Vector2f& point);
	sf::Vector2f ClampByTileMap(const sf::Vector2f& point);

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;
	void Reset();

	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;


	void AddScore(int s);
	void AddHiScore(int s);
	void SaveHiScore();
	void LoadHiScore();

	void ZombieClear();
	void SetHitBox();
};

