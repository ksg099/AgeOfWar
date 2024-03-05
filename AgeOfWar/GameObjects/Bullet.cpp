#include "pch.h"
#include "Bullet.h"
#include "SceneGame.h"
#include "Zombie.h"

Bullet::Bullet(const std::string& name)
	: SpriteGo(name)
{
}

void Bullet::Fire(const sf::Vector2f& dir, float s, int d)
{
	direction = dir;
	speed = s;
	damage = d;
	SetRotation(Utils::Angle(direction));
}

void Bullet::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/bullet.png");
	SetOrigin(Origins::ML);
	SetScale({ 2.f,2.f });
	GetHitBox();
}

void Bullet::Reset()
{
	SpriteGo::Reset();
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
}

void Bullet::Update(float dt)
{
	SetPosition(position + direction * speed * dt);

	if (sceneGame != nullptr)
	{
		if (!sceneGame->IsInTileMap(position))
		{
			SetActive(false);
			sceneGame->RemoveGo(this);
		}
	}
}

void Bullet::FixedUpdate(float dt)
{
	auto& list = sceneGame->GetZombieList();
	for (auto go : list)
	{
		if (!go->GetActive())
			continue;

		if (GetGlobalBounds().intersects(go->GetGlobalBounds()))
		{
			SetActive(false);
			sceneGame->RemoveGo(this);

			Zombie* zombie = dynamic_cast<Zombie*>(go);
			if (zombie != nullptr)
			{
				zombie->OnDamage(damage);
			}
			break;
		}
	}
}
