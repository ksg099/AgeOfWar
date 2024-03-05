#include "pch.h"
#include "TitleScene.h"
#include "SpriteGo.h"
#include "TextGo.h"


TitleScene::TitleScene(SceneIds id)
	:Scene(id)
{
}

void TitleScene::Init()
{	
	Scene::Init();
	titleTexture = new SpriteGo("Title");
	//titleTexture->SetOrigin(Origins::MC);
	titleTexture->SetTexture("graphics/ZombieSurvival.png");
	AddGo(titleTexture);


	uiText = new TextGo("uiText");
	uiText->Set(fontResMgr.Get("fonts/zombiecontrol.ttf"), "", 75, sf::Color::White);
	uiText->SetString("Press AnyKey To Start!");
	uiText->SetPosition({ 1920.f / 2, 1080.f - 200 });
	uiText->SetOrigin(Origins::MC);
	AddGo(uiText);

	SOUND_MGR.PlayBgm("sound/MainBgm.wav", true);
}

void TitleScene::Release()
{
	Scene::Release();
}

void TitleScene::Enter()
{
	Scene::Enter();
}

void TitleScene::Update(float dt)
{
	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter({ centerPos });

	if (InputMgr::AnyKeyDown())
	{
		SCENE_MGR.ChangeScene(SceneIds::SceneGame);
	}
	
}

void TitleScene::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
