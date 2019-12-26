#ifndef MINIMAP_H
#define MINIMAP_H

class Minimap
{
public:
	std::list<sf::RectangleShape> shapes;
public:
	Minimap();
	
	void render(sf::RenderTarget* target = NULL);
};

#include <Source/Minimap.cpp>
#endif
