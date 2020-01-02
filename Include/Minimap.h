#ifndef MINIMAP_H
#define MINIMAP_H

class Minimap
{
public:
	std::list<sf::RectangleShape> shapes;
public:
	Minimap();
	
	sf::Color roomColor;
	sf::Color corridorColor;
	
	void render(sf::RenderTarget* target = NULL);
};

#include <Source/Minimap.cpp>
#endif
