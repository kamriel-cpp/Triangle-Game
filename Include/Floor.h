#ifndef FLOOR_H
#define FLOOR_H

class Floor
{
private:
	sf::Vector2f	roomSize;
	float			corridorWidth;
	float			corridorLength;
	sf::Color 		floorColor;
	float			wallThickness;
	sf::Color 		wallColor;

	sf::Vector2i 	minRoomsCoords;
	sf::Vector2i 	maxRoomsCoords;

	void initVariables();
public:
	Floor();
	Floor(const Floor& other) = default;
	virtual ~Floor();

	int number;

	std::list<Room*> rooms;
	std::list<sf::RectangleShape*> walls;
	std::list<sf::RectangleShape*> doors;
	sf::Vector2f centerPosition;
	sf::Vector2f startRoomPosition;
	sf::Vector2f lastRoomPosition;
	
	sf::Vector2f mapCoordsToPixel(const sf::Vector2i &point) const;

	const sf::Vector2f& getRoomSize();
	
	void closeRoom(unsigned int index);
	void destroyAllDoors();

	void setRoomSize(sf::Vector2f room_size);
	void fillRoomsList(unsigned char floor[50][50]);
	void fillWallsList(unsigned char floor[50][50]);

	void generate();
	void destroy();

	void render(sf::RenderTarget* target = nullptr);
};

#include <Source/Floor.cpp>
#endif
