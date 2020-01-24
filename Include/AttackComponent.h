#ifndef ATTACKCOMPONENT_H
#define ATTACKCOMPONENT_H
#include <Include/Bullet.h>

class AttackComponent
{
private:
	bool canShoot;
	bool canPick;
	bool canDash;
	float shootingCooldown;
	float pickingCooldown;
	float dashingCooldown;
	float shootingTimer;
	float pickingTimer;
	float dashingTimer;
	float damage;
public:
	AttackComponent(const bool can_shoot, const bool can_pick, const bool can_dash,
		const float& shooting_cooldown, const float& picking_cooldown, const float& dashing_cooldown, float damage);
	virtual ~AttackComponent();

	void shoot(std::list<Bullet*>* bullets, const sf::Vector2f& position, const float& rotation);
	void pick();
	void dash();

	void update(const float& dt);
};

#include <Source/AttackComponent.cpp>
#endif
