#ifndef ROOM_H
#define ROOM_H

class Room
{
public:
	sf::RectangleShape shape;

	sf::Vector2i floorCoord;

	sf::Vector2f centerPosition;
	sf::Vector2f leftSidePosition;
	sf::Vector2f rightSidePosition;
	sf::Vector2f upSidePosition;
	sf::Vector2f downSidePosition;

	sf::Vector2f size;
	sf::Color color;
	std::string tag;
	unsigned int index;

	bool isActive; //enemies can spawn in the active room; in an inactive cannot be spawned
public:
	Room() = default;
	Room(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color, const std::string& tag);
	virtual ~Room() = default;
	
	void render(sf::RenderTarget* target = nullptr);
};

#include <Source/Room.cpp>
#endif
