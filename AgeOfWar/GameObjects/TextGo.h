#pragma once
#include "GameObject.h"

class TextGo : public GameObject
{
protected:
	sf::Text text;

public:
	TextGo(const std::string& name = "");

	sf::FloatRect GetLocalBounds() override;
	sf::FloatRect GetGlobalBounds() override;

	void SetString(const std::string& str);
	void Set(const sf::Font& texture, const std::string& str, int size, const sf::Color& color);

	void SetFont(const std::string& textureId);
	void SetFont(const sf::Font& texture);

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void SetPosition(const sf::Vector2f& pos) override;
	void Translate(const sf::Vector2f& delta) override;
	void SetRotation(float r) override;
	void SetScale(const sf::Vector2f& scale) override;
	
	void SetFlipX(bool filp) override;
	void SetFlipY(bool filp) override;

	void Draw(sf::RenderWindow& window) override;
};

