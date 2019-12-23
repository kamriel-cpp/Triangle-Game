#pragma once
#ifndef DUNGEON_H
#define DUNGEON_H

class Dungeon
{
private:
	unsigned		floor[50][50];
	unsigned		roomCounter;
	sf::Vector2f	roomSize;
	float			corridorWidth;
	float			corridorLength;
	sf::Vector2f	center;

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

	std::list<sf::RectangleShape> shapes;

	void initVariables();
public:
	Dungeon();
	Dungeon(const Dungeon& other) = default;
	~Dungeon() = default;

	sf::Vector2f getCenter();
	std::list<sf::RectangleShape>& getShapesList();
	void setRoomSize(sf::Vector2f room_size);
	void addStartRoom();
	void addRoom(sf::Vector2u position);
	void addBonusRoom(sf::Vector2u position);
	void addCorridorHorizontal(sf::Vector2u position);
	void addCorridorVertical(sf::Vector2u position);
	void fillFloor();
	void fillShapesList();
	void generate();

	void render(sf::RenderTarget* target = NULL);
};

#include <Source/Dungeon.cpp>
#endif
