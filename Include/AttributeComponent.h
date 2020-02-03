#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H

class AttributeComponent
{
public:
	int level;
	int exp;
	int expNext;
	int attributePoints;

	int hp;
	int hpMax;
	float reloadTime;
	float spread;
	int damage;
	int bulletsPerShoot;
	float bulletSpeed;
	float bulletRadius;
public:
	AttributeComponent(const int level);

	void randomSelectAllAttributePoints();
	const bool selectAttributePoints(const int& choise);

	void resetHP();
	void loseHP(const int hp);
	void gainHP(const int hp);
	void loseEXP(const int exp);
	void gainEXP(const int exp);

	const bool isDead() const;

	void debugPrint();

	void updateLevel();
	void update();
};

#include <Source/AttributeComponent.cpp>
#endif
