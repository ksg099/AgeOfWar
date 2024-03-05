#include "pch.h"
#include "Player.h"
#include "TileMap.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "Item.h";
#include "UiHud.h"
#include "ItemSpawner.h"

Player::Player(const std::string& name)
	: SpriteGo(name)
{
}

void Player::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/player.png");
	SetOrigin(Origins::MC);

	isFiring = false;
	fireTimer = fireInterval;
}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Reset()
{
	SpriteGo::Reset();
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

	isFiring = false;
	fireTimer = fireInterval;

	hp = 100;
	maxHp = 100;
	sceneGame->GetHud()->SetHp(hp, maxHp);

	ammo = maxAmmo;

	isAlive = true;
	isNoDamage = false;
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::R)) {

		int count = sceneGame->GetHud()->GetbulletCount();
		int total = sceneGame->GetHud()->Getbullettotal();
		if (total == 0)
			return;
		if (total >= 20)
		{
			count = 20;
			total -= 20;
		}
		else
		{
			count = total;
			total = 0;
		}
			sceneGame->GetHud()->SetAmmo(count, total);
	}


	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);

	look = mouseWorldPos - position;
	Utils::Normalize(look);

	SetRotation(Utils::Angle(look));

	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);
	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Normalize(direction);
	}

	sf::Vector2f pos = position + direction * speed * dt;
	if (sceneGame != nullptr)
	{
		pos = sceneGame->ClampByTileMap(pos);
	}
	SetPosition(pos);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		isFiring = true;
	}

	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left))
	{
		isFiring = false;
	}

	fireTimer += dt;
	if (isFiring && fireTimer > fireInterval && ammo > 0)
	{
		Fire();
		fireTimer = 0.f;
	}

	if (isNoDamage && !testMode)
	{
		noDamageTimer += dt;
		if (noDamageTimer > noDamageTime)
		{
			isNoDamage = false;
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::F3))
	{
		testMode = true;
		isNoDamage = true;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::F4))
	{
		testMode = false;
		isNoDamage = false;
	}

}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Player::Fire()
{

	if (sceneGame->GetHud()->GetbulletCount() <= 0)
		return;
	Bullet* bullet = new Bullet();
	bullet->Init();
	bullet->Reset();
	bullet->SetPosition(position);
	bullet->Fire(look, bulletSpeed, bulletDamage);
	sceneGame->AddGo(bullet);

	sceneGame->GetHud()->minusbullet(1);

	SOUND_MGR.PlaySfx("sound/shoot.wav");
	

	//수정
	std::cout <<"발사속도 : "<< fireInterval << std::endl;
	std::cout << "플레이어 속도 : " << speed << std::endl;
	std::cout << "MaxHp : " << maxHp << std::endl;
	std::cout << "Hp : " << hp << std::endl;

}

void Player::OnDamage(int damage)
{
	if (!isAlive || isNoDamage)
		return;

	hp -= damage;
	SOUND_MGR.PlaySfx("sound/zombiehit.wav");
	sceneGame->GetHud()->SetHp(hp, maxHp);

	isNoDamage = true;
	noDamageTimer = 0.f;

	if (hp <= 0)
	{
		hp = 0;
		sceneGame->GetHud()->SetHp(hp, maxHp);

		OnDie();
	}
}

void Player::OnDie()
{
	if (!isAlive)
		return;

	isAlive = false;
	SetActive(false);
}

void Player::OnItem(Item* item)
{
	switch (item->GetType())
	{
	case Item::Types::Ammo:
		ammo = item->GetValue();
		sceneGame->GetHud()->SetBulletCount(ammo);
		sceneGame->GetHud()->SetAmmo(sceneGame->GetHud()->GetbulletCount()
			, sceneGame->GetHud()->Getbullettotal());
		SOUND_MGR.PlaySfx("sound/pickup.wav");
		break;
	case Item::Types::Health:
		hp += item->GetValue();
		if (hp >= maxHp)
		{
			hp = maxHp;
		}
		sceneGame->GetHud()->SetHp(hp, maxHp);
		SOUND_MGR.PlaySfx("sound/pickup.wav");
		break;
	}
}

void Player::UpgradefireInterval(float f)
{
	if (fireInterval > 0.1f)
	{
		this->fireInterval -= f;
		if (fireInterval < 0.1f)
		{
			this->fireInterval = 0.1f;
		}
	}
}

void Player::UpgradeSpeed(float s)
{
	if (speed < 601.f)
	{
		this->speed += s;
		if (speed > 601.f)
		{
			this->speed = 600.f;
		}
	}
}

void Player::UpgradeMaxHp(int h)
{
	if (maxHp < 401.f)
	{
		this->maxHp += h;
		if (maxHp > 401.f)
		{
			this->maxHp = 400.f;
		}
	}
}

void Player::UpgradeFireDamage(int f)
{
	if (bulletDamage < 61.f)
	{
		this->bulletDamage += f;
		if (bulletDamage > 61.f)
		{
			this->bulletDamage = 60.f;
		}
	}
}

void Player::PlayerSetStat(float f, float s, int h)
{
	maxHp = h;
	speed = s;
	fireInterval = f;
}