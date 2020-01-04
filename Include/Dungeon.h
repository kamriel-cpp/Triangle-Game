#ifndef DUNGEON_H
#define DUNGEON_H

class Dungeon
{
private:
	unsigned char	floor[50][50];

	//Rooms settings
	sf::Vector2f	roomSize;
	float			corridorWidth;
	float			corridorLength;
	sf::Color 		floorColor;

	//Walls settings
	float			wallThickness;
	sf::Color 		wallColor;

	void initVariables();
public:
	Dungeon();
	Dungeon(const Dungeon& other) = default;
	virtual ~Dungeon() = default;

	sf::Vector2f centerPosition;
	sf::Vector2f startRoomPosition;
	sf::Vector2f lastRoomPosition;
	std::list<Room*> rooms;
	std::list<sf::RectangleShape> walls;
	
	const sf::Vector2f getRoomSize();

	void closeRoom(unsigned int index);
	void setRoomSize(sf::Vector2f room_size);
	void fillRoomsList();
	void fillWallsList();

	void generate();

	void render(sf::RenderTarget* target = nullptr);
};

#include <Source/Dungeon.cpp>
#endif
