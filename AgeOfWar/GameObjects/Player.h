#pragma once
#include "SpriteGo.h"

class SceneGame;
class Item;
class ItemSpawner;

class Player : public SpriteGo
{
protected:
	sf::Vector2f direction = { 0.f, 0.f };
	sf::Vector2f look = { 1.0f, 0.f };
	float speed = 200.f;

	SceneGame* sceneGame = nullptr;
	ItemSpawner* value = nullptr;

	float fireInterval = 0.5f;
	float bulletSpeed = 1000.f;

	int bulletDamage = 10;

	int maxHp = 200;
	int hp = 10;
	int maxAmmo = 40;
	int ammo = 20;

	bool isAlive = true;
	bool isNoDamage = false;
	bool testMode = false;
	float noDamageTime = 0.5f;
	float noDamageTimer = 0.f;

	bool isFiring = false;
	float fireTimer = 0.f;

public:
	Player(const std::string& name = "");
	~Player() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Fire();

	void OnDamage(int damage);
	void OnDie();
	void OnItem(Item* item);

	void UpgradefireInterval(float f);
	void UpgradeSpeed(float s);
	void UpgradeMaxHp(int h);
	void UpgradeFireDamage(int f);


	int GetHp() { return hp; }
	void PlayerSetStat(float f, float s, int h);
};

