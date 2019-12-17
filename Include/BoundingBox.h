#pragma once
#ifndef BOUNDINGNBOX_H
#define BOUNDINGNBOX_H

class BoundingBox
{
private:
	sf::RectangleShape&	shape;
	sf::RectangleShape	boundingBox;

public:
	BoundingBox				(sf::RectangleShape& shape);
	virtual ~BoundingBox	();

	const sf::Vector2f& getPosition() const;

	void setPosition		(const sf::Vector2f& position);
	void setPosition		(const float x, const float y);
	
	bool intersects			(const sf::FloatRect& frect);
	void update				(const float& dt);
	void render				(sf::RenderTarget* target = NULL);
};

#include <Source/BoundingBox.cpp>
#endif
