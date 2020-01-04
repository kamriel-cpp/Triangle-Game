#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Triangle
{
private:
	MovementComponent* movementComponent;

	void initMovementComponent();
public:
 	Enemy(const sf::Vector2f& position, sf::Color color);
 	virtual ~Enemy();
	
	bool intersectsWall;
	std::list<sf::RectangleShape> wallCheckers;

	void move(float dir_x, float dir_y, const float& dt);
	void move(float offsetX, float offsetY);
	void move(const sf::Vector2f& offset);
	void resetVelocityX();
	void resetVelocityY();

	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};

#include <Source/Enemy.cpp>
#endif
