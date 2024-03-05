#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "ZombieSpawner.h"
#include "ItemSpawner.h"
#include "UiHud.h"
#include "Upgrade.h"


SceneGame::SceneGame(SceneIds id)
	: Scene(id)
{

}

void SceneGame::SetStatus(Status newStatus)
{
	currentStatus = newStatus;
	switch (currentStatus)
	{
	case SceneGame::Status::Title:
		FRAMEWORK.SetTimeScale(0.f);
		break;
	case SceneGame::Status::Playing:
		FRAMEWORK.SetTimeScale(1.f);
		break;
	case SceneGame::Status::NextWave:
		FRAMEWORK.SetTimeScale(0.f);
		break;
	case SceneGame::Status::GameOver:
		FRAMEWORK.SetTimeScale(0.f);
		break;
	case SceneGame::Status::Pause:
		FRAMEWORK.SetTimeScale(0.f);
		break;
	}
}

bool SceneGame::IsInTileMap(const sf::Vector2f& point)
{
	sf::FloatRect rect = tileMap->GetGlobalBounds();
	rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f);

	return rect.contains(point);;
}

sf::Vector2f SceneGame::ClampByTileMap(const sf::Vector2f& point)
{
	sf::FloatRect rect = tileMap->GetGlobalBounds();
	rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f);
	return Utils::Clamp(point, rect);
}

void SceneGame::Init()
{
	zspawners.push_back(new ZombieSpawner());
	value = new ItemSpawner("itemspawner");
	ispawners.push_back(value);

	for (auto s : zspawners)
	{
		s->SetPosition({ 0.f, 0.f });
		AddGo(s);
	}
	for (auto i : ispawners)
	{
		i->SetPosition({ 0.f, 0.f });
		AddGo(i);
	}
	player = new Player("Player");
	AddGo(player);

	tileMap = new TileMap("Background");
	tileMap->sortLayer = -1;
	AddGo(tileMap);

	crosshair = new SpriteGo("Crosshair");
	crosshair->sortLayer = -1;
	crosshair->SetTexture("graphics/crosshair.png");
	crosshair->SetOrigin(Origins::MC);

	AddGo(crosshair, Scene::Layers::Ui);

	hud = new UiHud("Hud");
	AddGo(hud, Scene::Layers::Ui);

	upui = new Upgrade("UP");
	AddGo(upui, Scene::Layers::Ui);
 
	exitMsg = new TextGo("exit");
	exitMsg->Set(fontResMgr.Get("fonts/zombiecontrol.ttf"), "", 90, sf::Color::Black);
	exitMsg->SetOrigin(Origins::MC);
	exitMsg->SetString("Exit? Then Press Esc");
	exitMsg->SetActive(false);
	AddGo(exitMsg, Layers::Ui);


	restartMsg = new TextGo("restart");
	restartMsg->Set(fontResMgr.Get("fonts/zombiecontrol.ttf"), "", 90, sf::Color::Black);
	restartMsg->SetOrigin(Origins::MC);
	restartMsg->SetString("Restart? Then Press Enter");
	restartMsg->SetActive(false);
	AddGo(restartMsg, Layers::Ui);

	pause = new TextGo("Pause");
	pause->Set(fontResMgr.Get("fonts/zombiecontrol.ttf"), "", 120, sf::Color::Red);
	pause->SetOrigin(Origins::MC);
	pause->SetString("Pause");
	pause->SetActive(false);
	AddGo(pause, Layers::Ui);

	uiText = new TextGo("text");
	uiText->Set(fontResMgr.Get("fonts/zombiecontrol.ttf"), "", 120, sf::Color::Red);
	uiText->SetOrigin(Origins::MC);
	uiText->SetString("Game Over!");
	uiText->SetActive(false);
	AddGo(uiText,Layers::Ui);

	uiMsg = new TextGo("msg");
	uiMsg->Set(fontResMgr.Get("fonts/zombiecontrol.ttf"), "", 75, sf::Color::White);
	uiMsg->SetOrigin(Origins::MC);
	uiMsg->SetString("Press Enter To Restart");
	uiMsg->SetActive(false);
	AddGo(uiMsg, Layers::Ui);

	LoadHiScore();

	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);

	TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));
	tileMap->SetPosition({ 0.f, 0.f });
	tileMap->SetOrigin(Origins::MC);
	player->SetPosition({0, 0});

	Scene::Enter();
	hud->SetScore(0);
	hud->SetHiScore(this->HiScore);
	hud->SetAmmo(0, 0);
	hud->SetHiScore(0);
	hud->SetAmmo(5, 20);
	
	SetStatus(Status::Playing);
	zspawners[0]->SetActive(false);
	zspawners[0]->Spawn(5);
	hud->SetHiScore(this->HiScore);
	hud->SetAmmo(20, 40);

	upui->AddFireCount(0);
	upui->AddSpeedCount(0);
	upui->AddHealthCount(0);
	upui->AddFireDamageCount(0);
	upui->AddMagazineCount(0);

	SetStatus(Status::Title);
	zspawners[0]->SetActive(false);
	wave = 1;
	hud->SetWave(wave);
	hud->SetFps(0);

	uiText->SetPosition({ centerPos.x,centerPos.y - 100.f });
	uiMsg->SetPosition({ centerPos.x,centerPos.y + 100.f });

	exitMsg->SetPosition({ centerPos.x,centerPos.y - 100.f });
	restartMsg->SetPosition({ centerPos.x,centerPos.y + 100.f });
	pause->SetPosition({ centerPos.x,centerPos.y - 300.f });

}

void SceneGame::Exit()
{
	Scene::Exit();
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);
}

void SceneGame::Reset()
{
	player->SetActive(true);
	wave = 1;
	hud->SetWave(wave);
	player->PlayerSetStat(0.5, 200, 100);
	auto& list = GetZombieList();
	for (auto Go : list)
	{
		if (!Go->GetActive())
			continue;
		Zombie* zombie = dynamic_cast<Zombie*>(Go);
		if (zombie != nullptr)
		{
			RemoveGo(zombie);
		}
	}
	uiMsg->SetActive(false);
	uiText->SetActive(false);
	exitMsg->SetActive(false);
	restartMsg->SetActive(false);
	pause->SetActive(false);
}

void SceneGame::Update(float dt)
{

	FindGoAll("Zombie", zombieList, Layers::World);

	hud->SetZombieCount(zombieList.size());
	SetHitBox();

	Scene::Update(dt);

	timer += dt;
	++fpsCount;

	if (timer >= 1)
	{
		fps = fpsCount;
		timer = 0;
		fpsCount = 0;
	}
	hud->SetFps(fps);

	crosshair->SetPosition(ScreenToUi((sf::Vector2i)InputMgr::GetMousePos()));

	sf::Vector2f worldViewCenter = worldView.getCenter();
	worldViewCenter = Utils::Lerp(worldViewCenter, player->GetPosition(), dt * 2.f);
	worldView.setCenter(worldViewCenter);
	

	switch (currentStatus)
	{
	case SceneGame::Status::Title:
		if (InputMgr::GetKeyDown(sf::Keyboard::Num1) && upui->GetFireCount() < 10)
		{
			player->UpgradefireInterval(0.04f);
			upui->SetActive(false);
			SetStatus(Status::Playing);
			upui->AddFireCount(1);
		}
		else if (InputMgr::GetKeyDown(sf::Keyboard::Num2) && upui->GetSpeedCount() < 10)
		{
			player->UpgradeSpeed(40.f);
			upui->SetActive(false);
			SetStatus(Status::Playing);
			upui->AddSpeedCount(1);
		}
		else if (InputMgr::GetKeyDown(sf::Keyboard::Num3) && upui->GetHealthCount() < 10)
		{
			player->UpgradeMaxHp(30);
			upui->SetActive(false);
			SetStatus(Status::Playing);
			upui->AddHealthCount(1);
		}
		else if (InputMgr::GetKeyDown(sf::Keyboard::Num4) && upui->GetFireDamageCount() < 5)
		{
			player->UpgradeFireDamage(10);
			upui->SetActive(false);
			SetStatus(Status::Playing);
			upui->AddFireDamageCount(1);
		}
		else if (InputMgr::GetKeyDown(sf::Keyboard::Num5) && upui->GetMagazineCount() < 5)
		{
			value->Ammovalue += 6;
			upui->SetActive(false);
			SetStatus(Status::Playing);
			upui->AddMagazineCount(1);
		}
		break;
	case SceneGame::Status::Playing:
		if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
		{
			SetStatus(Status::Pause);
		}
		if (zombieList.size() == 0)
		{
			SetStatus(Status::NextWave);
			upui->SetActive(true);
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			player->OnDie();
			SetStatus(Status::GameOver);
		}
		if (player->GetHp() <= 0)
		{
			SetStatus(Status::GameOver);
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Delete))
		{
			ZombieClear();
		}
		break;
	case SceneGame::Status::Pause:
		pause->SetActive(true);
		exitMsg->SetActive(true);
		//restartMsg->SetActive(true);

		if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
		{
			SCENE_MGR.ChangeScene(SceneIds::TitleScene);
			SetStatus(Status::Title);
			upui->SetActive(true);
			Reset();
		}
		break;
		//else if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
		//{
		//	//upui->Reset();
		//	upui->SetActive(true);
		//	Reset();
		//	SetStatus(Status::Playing);
		//}
		//break;
		//if (InputMgr::GetKeyDown(sf::Keyboard::Up))
		//{
		//	exitMsg->Set(fontResMgr.Get("fonts/zombiecontrol.ttf"), "", 70, sf::Color::Red);
		//	restartMsg->Set(fontResMgr.Get("fonts/zombiecontrol.ttf"), "", 70, sf::Color::Black);

		//	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
		//	{
		//		SCENE_MGR.ChangeScene(SceneIds::TitleScene);
		//	}
		//}
		//break;

		//if (InputMgr::GetKeyDown(sf::Keyboard::Down))
		//{
		//	restartMsg->Set(fontResMgr.Get("fonts/zombiecontrol.ttf"), "", 70, sf::Color::Red);
		//	exitMsg->Set(fontResMgr.Get("fonts/zombiecontrol.ttf"), "", 70, sf::Color::Black);

		//	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
		//	{
		//		SetStatus(Status::Playing);
		//	}
		//}
		//break;

	case SceneGame::Status::NextWave:
		player->SetPosition({ 0, 0 });
		SetStatus(Status::Title);
		hud->SetWave(++wave);
		zspawners[0]->Spawn(5 * wave);
		break;
	case SceneGame::Status::GameOver:
		uiMsg->SetActive(true);
		uiText->SetActive(true);
		if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
		{
			SCENE_MGR.ChangeScene(SceneIds::TitleScene);
			SetStatus(Status::Title);
			upui->SetActive(true);
			Reset();
		}
	}
}

void SceneGame::FixedUpdate(float dt)
{
	FindGoAll("Zombie", zombieList, Layers::World);
	Scene::FixedUpdate(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	
	Scene::Draw(window);
}

void SceneGame::AddScore(int s)
{
	this->Score += s;
	hud->SetScore(this->Score);
}

void SceneGame::AddHiScore(int s)
{
	if (Score > HiScore)
	{
		this->HiScore = this->Score;
		hud->SetHiScore(this->HiScore);
		SaveHiScore();
	}
}

void SceneGame::SaveHiScore()
{
	std::ofstream file("HiScore.txt");
	if (file.is_open())
	{
		file << this->HiScore;
		file.close();
	}
}

void SceneGame::LoadHiScore()
{
	std::ifstream file("HiScore.txt");

	if (file.is_open())
	{
		file >> this->HiScore;
		file.close();
		hud->SetHiScore(this->HiScore);
	}
}

void SceneGame::ZombieClear()
{
	auto& list = GetZombieList();
	for (auto Go : list)
	{
		if (!Go->GetActive())
			continue;
		Zombie* zombie = dynamic_cast<Zombie*>(Go);
		if (zombie != nullptr)
		{
			zombie->OnDie();
		}
	}
}

void SceneGame::SetHitBox()
{
	
	player->GetHitBox();
	auto& list = GetZombieList();
	for (auto Go : list)
	{
		if (!Go->GetActive())
			continue;
		Zombie* zombie = dynamic_cast<Zombie*>(Go);
		if (zombie != nullptr)
		{
			zombie->GetHitBox();
		}
	}
}