#pragma once
#include "Scene.h"

class SpriteGo;
class TextGo;

class TitleScene : public Scene
{
protected:
	SpriteGo* titleTexture = nullptr;
	TextGo* uiText = nullptr;
	sf::RenderWindow window;

public:
	TitleScene(SceneIds id);
	~TitleScene()override = default;

	void Init() override;
	void Release() override;

	void Enter() override;

	void Update(float dt) override;

	void Draw(sf::RenderWindow& window) override;
};

