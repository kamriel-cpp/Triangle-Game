#ifndef SHOOTCOMPONENT_H
#define SHOOTCOMPONENT_H
#include <Include/Bullet.h>

class ShootComponent
{
public:
	Unit* caster;
	float cooldown;
	float timer;
	int reloadPercent;
public:
	ShootComponent();
	virtual ~ShootComponent();

	void shoot(std::list<Bullet*>* bullets,
		Unit* caster, sf::Color color,
		const sf::Vector2f& position, const float& rotation,
		const int& spread, const int& damage,
		int bullets_per_shoot,
		const float& bullet_speed, const float& bullet_radius);

	void update(const float& dt, const float& shoots_per_second);
};

#include <Source/ShootComponent.cpp>
#endif
