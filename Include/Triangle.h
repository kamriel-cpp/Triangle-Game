#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H

enum movement_states { IDLE = 0, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };

class Triangle
{
private:
	sf::RectangleShape				head;
	std::list<sf::RectangleShape>	tail;
	sf::FloatRect					boundingBox;
	short unsigned					moveDirection;
	unsigned						length;
	int 							arr[255];
public:
 	Triangle				();
 	Triangle				(float x, float y, const short unsigned moveDirection);
 	Triangle& operator=	(const Triangle& other);
	virtual ~Triangle		();

	sf::FloatRect getBoundingRect	() const;
	sf::Vector2f getPosition		();
	void pushTail					();
	void setFillColor				(sf::Color color);
	void setPosition				(const float x, const float y);
	void setDirection				(const short unsigned moveDirection);
	void move						(const float& dt);
	void update						(const float& dt);
	void render						(sf::RenderTarget* target = NULL);
};

#include <Source/Triangle.cpp>
#endif
