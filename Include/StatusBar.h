#ifndef STATUSBAR_H
#define STATUSBAR_H

class StatusBar
{
public:
	sf::RectangleShape backShape;
	sf::RectangleShape frontShape;

	float border;

	sf::Color baseColor;
	sf::Color secondaryColor;
public:
	StatusBar(const sf::Vector2f& position, const sf::Vector2f& size, const float& border,
		const sf::Color& back_color, const sf::Color& front_base_color, const sf::Color& front_secondary_color);
	virtual ~StatusBar();

	void update(const float& modifier);
	void render(sf::RenderTarget* target);
};

#include <Source/StatusBar.cpp>
#endif
