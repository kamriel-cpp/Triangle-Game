#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Triangle
{
private:
	MovementComponent movementComponent;

	void initMovementComponent();
public:
 	Enemy();
 	~Enemy();

	void move(const float dir_x, const float dir_y, const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};

#include <Source/Enemy.cpp>
#endif
