#ifndef BULLET_H
#define BULLET_H
#include <Include/Effect.h>

class Bullet : public sf::CircleShape
{
public:
	float movingSpeed;
	float damage;
public:
	Bullet(const sf::Vector2f& position, const sf::Color& color, const float& radius, const float& rotation, const float& moving_speed, float damage);
	void explode(std::list<Effect*>* effects);
	void update(const float& dt);
};

#include <Source/Bullet.cpp>
#endif
