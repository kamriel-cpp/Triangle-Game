#ifndef MINIMAP_H
#define MINIMAP_H

class Minimap
{
public:
	std::list<sf::RectangleShape> dungeon;
	sf::CircleShape player;

	Player* ptrPlayer;
public:
	Minimap();
	
	float mapFactor;
	float playerFactor;
	sf::Color roomColor;
	sf::Color corridorColor;
	sf::Color playerColor;
	
	void initShapes(Dungeon& dungeon, Player& player);
	
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};

#include <Source/Minimap.cpp>
#endif
