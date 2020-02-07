#ifndef SHOOTCOMPONENT_H
#define SHOOTCOMPONENT_H
#include <Include/Unit.h>
#include <Include/Bullet.h>

class ShootComponent
{
public:
	Unit* caster;
	float cooldown;
	float timer;
public:
	ShootComponent();
	virtual ~ShootComponent();

	void shoot(Unit* caster, std::list<Bullet*>* bullets,
		const sf::Vector2f& position, const float& rotation,
		const int& spread, const int& damage,
		int bullets_per_shoot,
		const float& bullet_speed, const float& bullet_radius);

	void update(const float& dt, const float& cooldown);
};

#include <Source/ShootComponent.cpp>
#endif
