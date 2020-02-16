#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H

class AttributeComponent
{
public:
	int lvl;				///Level
	int exp;				///EXPerience
	long expNext;			///EXPerience for NEXT level
	int aps;				///Attribute PointS
	int hp;					///HitPoints
	int mhp;				///Maximum HitPoints
	int sps;				///Shoots Per Second
	int spr;				///SPRead
	int dmg;				///DaMaGe
	int bps;				///Bullets Per Shoot
	int bsp;				///Bullet SPeed
	int brd;				///Bullet RaDius

	bool wasChangedLVL;
	bool wasChangedEXP;
	bool wasChangedAPS;
	bool wasChangedHP;
private:
	const bool upgradeMHP();
	const bool upgradeSPS();
	const bool upgradeSPR();
	const bool upgradeDMG();
	const bool upgradeBPS();
	const bool upgradeBSP();
	const bool upgradeBRD();
public:
	AttributeComponent(const int level);

	void randomDistributeAPS();
	const bool manualDistributeAPS(const int& choise);

	void resetHP();
	void loseHP(const int hp);
	void gainHP(const int hp);
	void loseEXP(const int exp);
	void gainEXP(const int exp);
	const bool isDead() const;

	void debugPrint();

	void updateLevel();
};

#include <Source/AttributeComponent.cpp>
#endif
