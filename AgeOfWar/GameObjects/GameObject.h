#pragma once

class GameObject
{
protected:
	bool active = true;

	Origins originPreset = Origins::TL;
	sf::Vector2f origin = { 0.f, 0.f };
	sf::Vector2f position = { 0.f, 0.f };
	float rotation = 0.f; // degree
	sf::Vector2f scale = { 1.f, 1.f };

	bool isFlipX = false;
	bool isFlipY = false;

public:
	GameObject(const std::string& name = "");
	virtual ~GameObject();

	static bool CompareDrawOrder(const GameObject& lhs, const GameObject& rhs)
	{
		if (lhs.sortLayer != rhs.sortLayer)
		{
			return lhs.sortLayer < rhs.sortLayer;
		}
		return lhs.sortOrder < rhs.sortOrder;
	}

	static bool CompareDrawOrder(const GameObject* lhs, const GameObject* rhs)
	{
		if (lhs->sortLayer != rhs->sortLayer)
		{
			return lhs->sortLayer < rhs->sortLayer;
		}
		return lhs->sortOrder < rhs->sortOrder;
	}

	bool operator<(const GameObject& rhs)
	{
		if (sortLayer != rhs.sortLayer)
		{
			return sortLayer < rhs.sortLayer;
		}
		return sortOrder < rhs.sortOrder;
	}

	bool GetActive() const { return active; }
	sf::Vector2f GetOrigin() const { return origin; }
	sf::Vector2f GetPosition() const { return position; }
	float GetRotation() const { return rotation; }
	sf::Vector2f GetScale() const { return scale; }
	bool GetFlipX() const { return isFlipX; }
	bool GetFlipY() const { return isFlipY; }

	virtual sf::FloatRect GetLocalBounds() { return  sf::FloatRect(); }
	virtual sf::FloatRect GetGlobalBounds() { return  sf::FloatRect(position, { 0.f, 0.f }); }

	virtual void SetActive(bool active) { this->active = active; }
	virtual void SetOrigin(Origins preset);
	virtual void SetOrigin(const sf::Vector2f& newOrigin)
	{
		originPreset = Origins::Custom;
		origin = newOrigin;
	}

	virtual void SetPosition(const sf::Vector2f& pos) { position = pos; }
	virtual void Translate(const sf::Vector2f& delta) { position += delta; }
	virtual void SetRotation(float r) { rotation = r; }
	virtual void SetScale(const sf::Vector2f& scale);

	virtual void SetFlipX(bool flip) {  isFlipX = flip ; }
	virtual void SetFlipY(bool flip) { isFlipY = flip; }

	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void LateUpdate(float dt);
	virtual void FixedUpdate(float dt);
	virtual void Draw(sf::RenderWindow& window);

	std::string name = "";
	int sortLayer = 0;
	int sortOrder = 0;
};

