#include "pch.h"
#include "SceneDev1.h"
#include "rapidcsv.h"
#include "ZombieTable.h"
#include "AniTest2.h"
#include "AniTest.h"



SceneDev1::SceneDev1(SceneIds id) : Scene(id)
{
}

SceneDev1::~SceneDev1()
{
}

void SceneDev1::Init()
{

	AddGo(new AniTest());
	//AddGo(new AniTest2());

	Scene::Init();
}

void SceneDev1::Release()
{
	Scene::Release();
}

void SceneDev1::Enter()
{

	Scene::Enter();

	std::cout << ZOMBIE_TABLE->Get(Zombie::Types::Bloater).nameId << std::endl;
	std::cout << ZOMBIE_TABLE->Get(Zombie::Types::Bloater).attackInterval << std::endl;
	std::cout << ZOMBIE_TABLE->Get(Zombie::Types::Bloater).damage << std::endl;
	std::cout << ZOMBIE_TABLE->Get(Zombie::Types::Bloater).maxHp << std::endl;
	std::cout << ZOMBIE_TABLE->Get(Zombie::Types::Bloater).speed << std::endl;
	std::cout << ZOMBIE_TABLE->Get(Zombie::Types::Bloater).textureId << std::endl;
}

void SceneDev1::Exit()
{
	Scene::Exit();
}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);

	//if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	//{
	//	SceneMgr::Instance().ChangeScene(SceneIds::SceneDev2);
	//}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		std::cout << STRING_TABLE->Get("TITLE") << std::endl;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		STRING_TABLE->Load(Languages::Korean);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
	{
		STRING_TABLE->Load(Languages::English);
	}
}
