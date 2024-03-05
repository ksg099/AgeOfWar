#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
#include "TextGo.h"

class UiHud : public GameObject
{
protected:
	std::string formatScore = "SCORE: ";
	std::string formatHighScore = "HIGH SCORE: ";
	std::string formatWave = "WAVE: ";
	std::string formatZombieCount = "ZOMBIES: ";

	//���׷��̵�
	


	TextGo textScore;
	TextGo textHiScore;

	SpriteGo imgAmmoIcon;
	TextGo textAmmo;
	sf::RectangleShape gaugeHp;
	TextGo textWave;
	TextGo textZombieCount;
	TextGo uiFps;

	sf::Vector2f gaugeHpSize = { 300.f, 25.f };

	sf::Vector2f referenceResolution = { 1920.f, 1080.f };
	sf::Vector2f resolution = referenceResolution;


	bool isChecking = false;

	int bulletCount = 6;
	int totalCount = 24;

public:
	UiHud(const std::string& name = "");
	~UiHud() override = default;

	void SetResoultion(const sf::Vector2f resoution);

	void SetScore(int s);
	void SetHiScore(int s);

	void SetAmmo(int current, int total);
	void SetHp(int hp, int max);
	void SetWave(int w);
	void SetZombieCount(int count);

	void SetFps(int fps);
	void Update(float dt);

	void Init() override;
	void Reset() override;
	void Draw(sf::RenderWindow& window) override;

	void SetBulletCount(int b);
	void minusbullet(int b);
	int GetbulletCount() const { return bulletCount; }
	int Getbullettotal() const { return totalCount; }

};

