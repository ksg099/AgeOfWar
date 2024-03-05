#include "pch.h"
#include "Upgrade.h"

Upgrade::Upgrade(const std::string& name)
	:GameObject(name)
{
}

void Upgrade::Init()
{
	float textSize = 80.f;
	sf::Font& font = RES_MGR_FONT.Get("fonts/zombiecontrol.ttf");
	
	textMaxUp.Set(font, formatMaxUpgrade, 70, sf::Color::White);
	textMaxUp.SetPosition({ 1920.f / 2.f , 200 });
	textMaxUp.SetOrigin(Origins::MC);

	textFireUp.Set(font, formatFireSpeed, textSize, sf::Color::White);
	textFireUp.SetPosition({ 1920.f / 2.f , 330 });
	textFireUp.SetOrigin(Origins::MC);

	textSpeedUp.Set(font, formatPlayerSpeed, textSize, sf::Color::White);
	textSpeedUp.SetPosition({ 1920.f / 2.f , 460 });
	textSpeedUp.SetOrigin(Origins::MC);

	textHealthUp.Set(font, formatMaxHealth, textSize, sf::Color::White);
	textHealthUp.SetPosition({ 1920.f / 2.f , 590 });
	textHealthUp.SetOrigin(Origins::MC);

	textFireDamageUp.Set(font, formatFireDamage, textSize, sf::Color::White);
	textFireDamageUp.SetPosition({ 1920.f / 2.f , 720 });
	textFireDamageUp.SetOrigin(Origins::MC);

	textMagazinehUp.Set(font, formatMagazine, textSize, sf::Color::White);
	textMagazinehUp.SetPosition({ 1920.f / 2.f , 840 });
	textMagazinehUp.SetOrigin(Origins::MC);
	//Ui
	upgradeUi.Init();
	upgradeUi.SetTexture("graphics/ZombieSurvival.png");
	upgradeUi.SetPosition({ 1920.f / 2.f , 1080.f / 2.f });
	upgradeUi.SetOrigin(Origins::MC);
	//upgradeUi.SetScale({ 0.5f, 0.5f });
}

void Upgrade::Reset()
{
	FireCount = 0;
	SpeedCount = 0;
	HealthCount = 0;
	FireDamageCount = 0;
	MagazineCount = 0;
}

void Upgrade::Draw(sf::RenderWindow& window)
{
	//ui
	upgradeUi.Draw(window);
	textMaxUp.Draw(window);
	textFireUp.Draw(window);
	textSpeedUp.Draw(window);
	textHealthUp.Draw(window);
	textFireDamageUp.Draw(window);
	textMagazinehUp.Draw(window);
}

void Upgrade::AddFireCount(int f)
{
	this->FireCount += f;
	textFireUp.SetString(formatFireSpeed + std::to_string(this->FireCount));
	
}

void Upgrade::AddSpeedCount(int s)
{
	this->SpeedCount += s;
	textSpeedUp.SetString(formatPlayerSpeed + std::to_string(this->SpeedCount));
}

void Upgrade::AddHealthCount(int h)
{
	this->HealthCount += h;
	textHealthUp.SetString(formatMaxHealth + std::to_string(this->HealthCount));
}

void Upgrade::AddFireDamageCount(int d)
{
	this->FireDamageCount += d;
	textFireDamageUp.SetString(formatFireDamage + std::to_string(this->FireDamageCount));
}

void Upgrade::AddMagazineCount(int m)
{
	this->MagazineCount += m;
	textMagazinehUp.SetString(formatMagazine + std::to_string(this->MagazineCount));
}
