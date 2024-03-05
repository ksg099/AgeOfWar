#include "pch.h"
#include "UiHud.h"

UiHud::UiHud(const std::string& name)
	: GameObject(name)
{
}

void UiHud::SetResoultion(const sf::Vector2f resoution)
{
}

void UiHud::SetScore(int s)
{
	textScore.SetString(formatScore + std::to_string(s));
}

void UiHud::SetHiScore(int s)
{
	textHiScore.SetString(formatHighScore + std::to_string(s));
}

void UiHud::SetAmmo(int current, int total)
{

	bulletCount = current;
	totalCount = total;
	textAmmo.SetString(std::to_string(current) + "/" + std::to_string(total));
}

void UiHud::SetHp(int hp, int max)
{
	float value = (float)hp / max;
	gaugeHp.setSize({ gaugeHpSize.x * value, gaugeHpSize.y });
}

void UiHud::SetWave(int w)
{
	textWave.SetString(formatWave + std::to_string(w));
}

void UiHud::SetZombieCount(int count)
{
	textZombieCount.SetString(formatZombieCount + std::to_string(count));
}

void UiHud::SetFps(int fps)
{
	uiFps.SetString("Fps:" + std::to_string(fps));
}

void UiHud::Update(float dt)
{
	GameObject::Update(dt);
	if (InputMgr::GetKeyDown(sf::Keyboard::F1))
	{
		isChecking = true;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::F2))
	{
		isChecking = false;
	}
}

void UiHud::Init()
{
	textScore.Init();
	textHiScore.Init();
	imgAmmoIcon.Init();
	textAmmo.Init();
	textWave.Init();
	textZombieCount.Init();
	uiFps.Init();


	float textSize = 50.f;
	sf::Font& font = RES_MGR_FONT.Get("fonts/zombiecontrol.ttf");

	textScore.Set(font, "", textSize, sf::Color::White);
	textHiScore.Set(font, "", textSize, sf::Color::White);
	textAmmo.Set(font, "", textSize, sf::Color::White);
	textWave.Set(font, "", textSize, sf::Color::White);
	textZombieCount.Set(font, "", textSize, sf::Color::White);
	imgAmmoIcon.SetTexture("graphics/ammo_icon.png");
	gaugeHp.setFillColor(sf::Color::Red);
	gaugeHp.setSize(gaugeHpSize);

	uiFps.Set(font, "", textSize, sf::Color::Green);
	uiFps.SetOrigin(Origins::TL);

	textScore.SetOrigin(Origins::TL);
	textHiScore.SetOrigin(Origins::TR);
	imgAmmoIcon.SetOrigin(Origins::BL);
	textAmmo.SetOrigin(Origins::BL);
	Utils::SetOrigin(gaugeHp, Origins::BL);
	textWave.SetOrigin(Origins::BR);
	textZombieCount.SetOrigin(Origins::BR);

	// Top
	float topY = 25.f;
	textScore.SetPosition({ 25.f, topY });
	textHiScore.SetPosition({ referenceResolution.x - 25.f, topY });
	uiFps.SetPosition({ 25.f,topY + 50.f });

	// Bottom
	float BottomY = referenceResolution.y - 25.f;;
	imgAmmoIcon.SetPosition({ 25.f, BottomY + 10.f });
	textAmmo.SetPosition({ 100.f, BottomY } );
	gaugeHp.setPosition( { 300.f, BottomY } );

	textWave.SetPosition({ referenceResolution.x - 400.f, BottomY });
	textZombieCount.SetPosition({ referenceResolution.x - 25.f, BottomY });
}

void UiHud::Reset()
{
	textScore.Reset();
	textHiScore.Reset();
	imgAmmoIcon.Reset();
	textAmmo.Reset();
	textWave.Reset();
	textZombieCount.Reset();
	uiFps.Reset();
}

void UiHud::Draw(sf::RenderWindow& window)
{
	
	textScore.Draw(window);
	textHiScore.Draw(window);
	imgAmmoIcon.Draw(window);
	textAmmo.Draw(window);
	window.draw(gaugeHp);
	textWave.Draw(window);
	textZombieCount.Draw(window);
	if (isChecking)
	{
		uiFps.Draw(window);
	}

}

void UiHud::SetBulletCount(int b)
{
	totalCount += b;
}

void UiHud::minusbullet(int b)
{
	bulletCount -= b;
	SetAmmo(bulletCount, totalCount);
}