#ifndef DUNGEON_H
#define DUNGEON_H

class Dungeon
{
private:
	unsigned char	floor[50][50];
	unsigned char	roomCounter;
	sf::Vector2f	roomSize;
	float			corridorWidth;
	float			corridorLength;
	float			wallThickness;

	sf::Color 		mainColor;
	sf::Color 		mainRoomColor;
	sf::Color 		startRoomColor;
	sf::Color 		lastRoomColor;
	sf::Color 		corridorColor;

	float 			roomsOutlineThickness;

	std::list<sf::Vector2u> rooms;
	std::list<sf::Vector2u> bonusRooms;
	std::list<sf::Vector2u> corridorsHorizontal;
	std::list<sf::Vector2u> corridorsVertical;

	void initVariables();
public:
	sf::Vector2f center;
	std::list<sf::RectangleShape> shapes;
	std::list<sf::RectangleShape> walls;
	
	Dungeon();
	Dungeon(const Dungeon& other) = default;
	~Dungeon() = default;

	void setRoomSize(sf::Vector2f room_size);
	void addStartRoom();
	void addRoom(sf::Vector2u position);
	void addBonusRoom(sf::Vector2u position);
	void addCorridorHorizontal(sf::Vector2u position);
	void addCorridorVertical(sf::Vector2u position);

	void fillFloor();
	void fillShapesList();
	void fillWallsList();

	void generate();

	void render(sf::RenderTarget* target = NULL);
};

#include <Source/Dungeon.cpp>
#endif
