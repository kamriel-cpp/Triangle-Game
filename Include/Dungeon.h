#ifndef DUNGEON_H
#define DUNGEON_H

class Dungeon
{
private:
	unsigned char	floor[50][50];

	//Rooms settings
	unsigned char	roomCounter;
	sf::Vector2f	roomSize;
	float			corridorWidth;
	float			corridorLength;
	sf::Color 		floorColor;

	//Walls settings
	float			wallThickness;
	sf::Color 		wallColor;

	//Room class
	class Room
	{
	public:
		sf::Vector2f centerPosition;
		sf::Vector2f leftSidePosition;
		sf::Vector2f rightSidePosition;
		sf::Vector2f upSidePosition;
		sf::Vector2f downSidePosition;
		
		sf::Vector2f size;
		sf::Color color;

		bool is_active; //enemies can spawn in the active room; in an inactive cannot be spawned
		unsigned int index; //just an indexer of rooms; for ease of use
	public:
		Room(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color);
		virtual ~Room();
		
	};

	//Lists the positions of rooms of each type in the array floor[][]
	std::list<sf::Vector2u> rooms;
	std::list<sf::Vector2u> bonusRooms;
	std::list<sf::Vector2u> corridorsHorizontal;
	std::list<sf::Vector2u> corridorsVertical;

	void initVariables();
public:
	Dungeon();
	Dungeon(const Dungeon& other) = default;
	virtual ~Dungeon() = default;

	sf::Vector2f center;
	std::list<sf::RectangleShape> shapes;
	std::list<sf::RectangleShape> walls;
	
	const sf::Vector2f getRoomSize();

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
