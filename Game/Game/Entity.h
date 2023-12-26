#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <optional>
#include <SFML/Graphics/Texture.hpp>

class Entity
{
public:
	explicit Entity(std::string const& filename, std::optional<sf::Vector2f> const size = std::nullopt);
	virtual void Draw(sf::RenderWindow& window);
	sf::Vector2f GetSize() const;
	sf::Sprite& GetImage();
	void SetOriginCenter();
	void Hide();
	void Show();
	bool IsHidden();
	void Flip();
	bool IsFlipped() const;
	void LoadImage
	(
		std::string const& filename,
		std::optional<sf::Vector2f> const size = std::nullopt
	);

private:
	sf::Sprite m_image;
	sf::Texture m_texture;
	bool m_hidden = false;
	bool m_flipped;
};
