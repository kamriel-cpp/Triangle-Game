#ifndef BULLET_H
#define BULLET_H
#include <Include/Effect.h>

class Bullet : public sf::CircleShape
{
public:
	float movingSpeed;
	int damage;
public:
	Bullet(const sf::Vector2f& position, const float& rotation,
		const sf::Color& color, const int& damage,
		const float& moving_speed, const float& radius);

	void explode(std::list<Effect*>* effects);
	void update(const float& dt);
};

#include <Source/Bullet.cpp>
#endif
