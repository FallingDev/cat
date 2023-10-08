#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <optional>
#include <SFML/Graphics/Texture.hpp>

class Entity
{
public:
	explicit Entity(std::string const& filename, std::optional<sf::Vector2f> const size = std::nullopt);
	void Draw(sf::RenderWindow& window) const;
	sf::Vector2f GetSize() const;
	sf::Vector2f GetPosition() const;
	void SetPosition(sf::Vector2f const position);
	void SetRotation(float const angle);
	void Rotate(float const angle);
	sf::Sprite& GetImage();

	void LoadImage
	(
		std::string const& filename,
		std::optional<sf::Vector2f> const size = std::nullopt
	);

private:
	sf::Sprite m_image;
	sf::Texture m_texture;
};
