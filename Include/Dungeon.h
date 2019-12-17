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

	std::list<sf::Vector2u> rooms;
	std::list<sf::Vector2u> bonusRooms;
	std::list<sf::Vector2u> corridorsHorizontal;
	std::list<sf::Vector2u> corridorsVertical;
public:
	Dungeon();
	Dungeon(const Dungeon& other) = default;
	~Dungeon() = default;

	void setRoomSize(sf::Vector2f room_size);
	void addStartRoom();
	void addRoom(sf::Vector2u position);
	void addBonusRoom(sf::Vector2u position);
	void addCorridorHorizontal(sf::Vector2u position);
	void addCorridorVertical(sf::Vector2u position);
	void generate();
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};

#include <Source/Dungeon.cpp>
#endif
