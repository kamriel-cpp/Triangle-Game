#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle
{
protected:
	sf::Color defaultColor;
	float defaultRadius;
	sf::Vector2f defaultOrigin;
	sf::Vector2f defaultScale;
	size_t defaultPointCount;
public:
	sf::CircleShape shape;
public:
 	Triangle();

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target = NULL);
};

#include <Source/Triangle.cpp>
#endif
