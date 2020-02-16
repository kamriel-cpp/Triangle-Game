#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

class ProgressBar
{
public:
	sf::Text info;

	sf::RectangleShape backShape;
	sf::RectangleShape frontShape;

	int borderPercent;

	sf::Color barBaseColor;
	sf::Color barSecondaryColor;

	sf::Color infoBaseColor;
	sf::Color infoSecondaryColor;

	int infoType;
public:
	ProgressBar(sf::Font* font, const unsigned int& character_size,
		const sf::Vector2f& position, const sf::Vector2f& size,
		const float& outline_thickness, const int& max_base_percent,
		const sf::Color& back_fill_color, const sf::Color& back_outline_color,
		const sf::Color& front_base_color, const sf::Color& front_secondary_color,
		const sf::Color& info_base_color, const sf::Color& info_secondary_color,
		const int& info_type);
	virtual ~ProgressBar();

	void update(const float& current_value, const float& max_value);
	void update(const float& progress_percent);
	void render(sf::RenderTarget* target = nullptr);
};

#include <Source/ProgressBar.cpp>
#endif
