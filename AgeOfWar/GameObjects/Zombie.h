#pragma once
#include "SpriteGo.h"
#include "Player.h"
#include "UiHud.h"
#include "Item.h"
#include "ItemSpawner.h"

class SceneGame;
class ItemSpawner;

class Zombie : public SpriteGo
{
public:
	enum class Types
	{
		Bloater,
		Chaser,
		Crawler,
	};
	static const int TotalTypes = 3;
	static Zombie* Create(Types zombieType);

protected:
	Types type;

	int maxHp;
	float speed;
	int damage;
	float attackInterval;
	float attackTimer = 0.f;

	int hp;
	

	Player* player = nullptr;
	SceneGame* sceneGame = nullptr;
	ItemSpawner* itemspawner;

	sf::Vector2f direction;
	bool isAlive = true;

	

	Zombie(const std::string& name = "");

public:
	~Zombie() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void OnDamage(int damage);
	void OnDie();

	void PlayBloodEffect();
};

