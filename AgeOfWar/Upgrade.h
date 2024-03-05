#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
#include "TextGo.h"
class Upgrade : public GameObject
{

protected:
	SpriteGo upgradeUi;
	std::string formatMaxUpgrade = "UPGRADE MAX: 10";
	std::string formatFireSpeed = "1- UPGRADE FIRE SPEED  UP: ";
	std::string formatPlayerSpeed = "2- UPGRADE REN SPEED  UP: ";
	std::string formatMaxHealth = "3- UPGRADE MAX HEALTH  UP: ";
	std::string formatFireDamage = "4- UPGRADE Fire Damage  UP: ";
	std::string formatMagazine = "5- UPGRADE MAGAZINE  UP: ";

	TextGo* text;
	
	
	TextGo textMaxUp;
	TextGo textFireUp;
	TextGo textSpeedUp;
	TextGo textHealthUp;
	TextGo textFireDamageUp;
	TextGo textMagazinehUp;

	int FireCount = 0;
	int SpeedCount = 0;
	int HealthCount = 0;
	int FireDamageCount = 0;
	int MagazineCount = 0;

	

public:
	Upgrade(const std::string& name = "");
	~Upgrade() override = default;

	void Init() override;
	void Reset() override;
	void Draw(sf::RenderWindow& window) override;

	void AddFireCount(int f);
	void AddSpeedCount(int s);
	void AddHealthCount(int h);
	void AddFireDamageCount(int d);
	void AddMagazineCount(int m);

	int GetFireCount() { return this->FireCount; }
	int GetSpeedCount() { return this->SpeedCount; }
	int GetHealthCount() { return this->HealthCount; }
	int GetFireDamageCount() { return this->FireDamageCount; }
	int GetMagazineCount() { return this->MagazineCount; }

	
};

