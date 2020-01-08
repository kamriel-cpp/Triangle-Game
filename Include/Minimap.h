#ifndef MINIMAP_H
#define MINIMAP_H

class Minimap
{
public:
	std::list<sf::RectangleShape> floor;
	sf::CircleShape player;
	sf::Vector2f floorOffset;
	sf::Vector2f windowOffset;

	Player* ptrPlayer;
public:
	Minimap(Floor& floor, Player& player, const sf::RenderWindow* window);
	
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
