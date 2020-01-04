#ifndef MINIMAP_H
#define MINIMAP_H

class Minimap
{
public:
	std::list<sf::RectangleShape> dungeon;
	sf::CircleShape player;

	Player* ptrPlayer;
public:
	Minimap(Dungeon& dungeon, Player& player);
	
	float mapFactor;
	float playerFactor;
	sf::Color roomColor;
	sf::Color corridorColor;
	sf::Color playerColor;
	
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

#include <Source/Minimap.cpp>
#endif
