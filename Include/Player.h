#pragma once
#ifndef PLAYER_H
#define PLAYER_H

class Player : public Triangle
{
private:
	MovementComponent movementComponent;
	sf::Vector2i* mousePosition;
	sf::Vector2f* mousePosition2;
	sf::Vector2f lookDir;

	void initMovementComponent();
public:
 	Player();
 	~Player();

 	void setMousePosition(sf::Vector2i* mousePosition);
 	void setMousePosition2(sf::Vector2f* mousePosition);
	void move(const float dir_x, const float dir_y, const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};

#include <Source/Player.cpp>
#endif
