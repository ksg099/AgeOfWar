#pragma once
#include "SpriteGo.h"

class SceneGame;

class Bullet : public SpriteGo
{
protected:
	sf::Vector2f direction;
	float speed;
	int damage = 0;

	SceneGame* sceneGame;

public:
	Bullet(const std::string& name = "");
	~Bullet() override = default;

	void Fire(const sf::Vector2f& dir, float s, int d);

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
};

