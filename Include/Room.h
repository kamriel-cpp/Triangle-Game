#ifndef ROOM_H
#define ROOM_H

class Room
{
private:
	std::list<sf::RectangleShape*> walls;
	std::list<sf::RectangleShape*> doors;
	
	void placeWall(const sf::Vector2f& position, const sf::Vector2f& size);
	void placeDoor(const sf::Vector2f& position, const sf::Vector2f& size);
public:
	sf::RectangleShape shape;
	sf::Vector2f size;
	sf::Color color;
	unsigned char tag;
	unsigned int index;
	float wallThickness;
	sf::Color wallColor;

	sf::Vector2i floorCoord;
	sf::Vector2f centerPosition;
	sf::Vector2f leftSidePosition;
	sf::Vector2f rightSidePosition;
	sf::Vector2f upSidePosition;
	sf::Vector2f downSidePosition;
	
	bool isVisited;
public:
	Room(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color,
		const unsigned char tag, const unsigned char nearby_cells[4]);
	virtual ~Room();
	
	const std::list<sf::RectangleShape*> getWalls() const;
	const std::list<sf::RectangleShape*> getDoors() const;

	void activateWaveSpawner();

	void open();
	void close();

	void render(sf::RenderTarget* target = nullptr);
};

#include <Source/Room.cpp>
#endif
