#ifndef UNIT_H
#define UNIT_H
#include <Include/Bullet.h>

class Unit : public sf::CircleShape
{
public:
	Unit() { }
	virtual ~Unit() { }

 	virtual void update(const float& dt, const sf::Vector2f& target_position) = 0;
	virtual void updateAutoShooting(Unit* caster, std::list<Bullet*>* bullets) = 0;
};

#include <Source/Unit.cpp>
#endif
