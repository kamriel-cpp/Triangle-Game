#ifndef BULLET_H
#define BULLET_H
#include <Include/Effect.h>

class Actor;

class Bullet : public sf::CircleShape
{
public:
	Actor* caster;
	int damage;
	float movingSpeed;
public:
	Bullet(Actor* caster, const sf::Vector2f& position, const float& rotation,
		const sf::Color& color, const int& damage,
		const float& moving_speed, const float& radius);
	virtual ~Bullet();

	void explode(std::list<Effect*>* effects);
	void update(const float& dt);
};

#include <Source/Bullet.cpp>
#endif
