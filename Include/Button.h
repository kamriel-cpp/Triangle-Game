#ifndef BUTTON_H
#define BUTTON_H

class Button
{
private:
	sf::RectangleShape	shape;
	sf::Font*			font;
	sf::Text			text;
	unsigned short		buttonState;

	sf::Color			textIdleColor;
	sf::Color			textHoverColor;
	sf::Color			textActiveColor;

	sf::Color			idleColor;
	sf::Color			hoverColor;
	sf::Color			activeColor;
public:
	bool wasPressed;
public:
	Button() = default;
	Button(float x, float y,
		   float offset_x, float offset_y, float width, float height,
		   sf::Font* font, std::string text, unsigned char character_size,
		   sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
		   sf::Color idle_color, sf::Color hover_color, sf::Color active_color);
	virtual ~Button() = default;
	
	const bool isPressed() const;
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget* target);
};

#include <Source/Button.cpp>
#endif
