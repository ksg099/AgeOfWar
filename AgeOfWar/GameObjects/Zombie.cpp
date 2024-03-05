#include "pch.h"
#include "Zombie.h"
#include "SceneGame.h"
#include "SpriteGoEffect.h"
#include "ZombieTable.h"
#include "UiHud.h"
#include "ItemSpawner.h"
#include "UiHud.h"
#include "Item.h"

Zombie* Zombie::Create(Types zombieType)
{
	Zombie* zombie = new Zombie("Zombie");
	zombie->type = zombieType;

	const DataZombie& data = ZOMBIE_TABLE->Get(zombieType);
	zombie->textureId = data.textureId;
	zombie->maxHp = data.maxHp;
	zombie->speed = data.speed;
	zombie->damage = data.damage;
	zombie->attackInterval = data.attackInterval;
	return zombie;
}

Zombie::Zombie(const std::string& name)
	: SpriteGo(name)
{
}

void Zombie::Init()
{
	SpriteGo::Init();
	SetTexture(textureId);
	SetOrigin(Origins::MC);
	
}

void Zombie::Release()
{
	SpriteGo::Release();
}

void Zombie::Reset()
{
	SpriteGo::Reset();

	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	itemspawner = dynamic_cast<ItemSpawner*>(SCENE_MGR.GetCurrentScene()->FindGo("itemspawner")); //
	
	isAlive = true;
	hp = maxHp;
	attackTimer = attackInterval;
}

void Zombie::Update(float dt)
{
	SpriteGo::Update(dt);

	if (!isAlive)
		return;
	direction = player->GetPosition() - position;
	Utils::Normalize(direction);

	SetRotation(Utils::Angle(direction));
	sf::Vector2f pos = position + direction * speed * dt;
	

	if (sceneGame != nullptr)
	{
		pos = sceneGame->ClampByTileMap(pos);
		
	}
	SetPosition(pos);
	
}

void Zombie::FixedUpdate(float dt)
{
	attackTimer += dt;

	if (attackTimer > attackInterval)
	{
		if (GetGlobalBounds().intersects(player->GetGlobalBounds()))
		{
			player->OnDamage(damage);
			attackTimer = 0.f;
		}
	}
}

void Zombie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Zombie::OnDamage(int damage)
{
	if (!isAlive)
		return;

	hp -= damage;
	SOUND_MGR.PlaySfx("sound/hit.wav");
	if (hp <= 0)
	{
		hp = 0;
		OnDie();
		sceneGame->AddScore(10);
		sceneGame->AddHiScore(10);
	}
}

void Zombie::OnDie()
{ 
	if (!isAlive)
		return;
	SOUND_MGR.PlaySfx("sound/splat.wav");
	isAlive = false;
	SetActive(false);
	sceneGame->RemoveGo(this);

	itemspawner->OnDrop(position);
	

	PlayBloodEffect();
}

void Zombie::PlayBloodEffect()
{
	SpriteGoEffect* effectBlood = new SpriteGoEffect();
	effectBlood->Init();
	effectBlood->SetOrigin(Origins::MC);
	effectBlood->SetTexture("graphics/blood.png");
	effectBlood->Reset();
	effectBlood->sortLayer = -1;
	effectBlood->sortOrder = 1;
	effectBlood->SetPosition(position);
	effectBlood->SetRotation(Utils::RandomRange(0.f, 360.f));
	sceneGame->AddGo(effectBlood);
}
