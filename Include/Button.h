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

	sf::Color			fillIdleColor;
	sf::Color			fillHoverColor;
	sf::Color			fillActiveColor;

	sf::Color			outlineIdleColor;
	sf::Color			outlineHoverColor;
	sf::Color			outlineActiveColor;
public:
	std::string			tag;
	bool				wasPressed;
public:
	Button() = default;
	Button(float x, float y,
		   float offset_x, float offset_y, float width, float height,
		   sf::Font* font, std::string text, std::string tag, unsigned char character_size,
		   sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
		   sf::Color fill_idle_color, sf::Color fill_hover_color, sf::Color fill_active_color,
		   sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent,
		   float outline_thickness = 0);
	virtual ~Button() = default;
	
	const sf::Vector2f& getPosition()
	{
		return this->shape.getPosition();
	}
	const bool isPressed() const;
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget* target = nullptr);
};

#include <Source/Button.cpp>
#endif
