#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Triangle
{
private:
	MovementComponent movementComponent;

	void initMovementComponent();
public:
 	Enemy();
 	Enemy(const sf::Vector2f& position);
 	virtual ~Enemy();

	void move(float dir_x, float dir_y, const float& dt);
	void move(float offsetX, float offsetY);
	void move(const sf::Vector2f& offset);

	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};

#include <Source/Enemy.cpp>
#endif
