#ifndef CORRIDOR_H
#define CORRIDOR_H

class Corridor : public Room
{
public:
	Corridor() = default;
	Corridor(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color, const unsigned char& type);
	virtual ~Corridor() = default;
};

#include <Source/Corridor.cpp>
#endif
