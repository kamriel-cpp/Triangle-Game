#pragma once
#ifndef MINIMAP_H
#define MINIMAP_H

class Minimap
{
private:
	std::list<sf::RectangleShape> shapes;
public:
	Minimap();
	
	void setShapesList(std::list<sf::RectangleShape> shapes);
	void render(sf::RenderTarget* target = NULL);
};

#include <Source/Minimap.cpp>
#endif
