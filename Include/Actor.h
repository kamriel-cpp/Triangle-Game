#ifndef ACTOR_H
#define ACTOR_H
#include <Include/Unit.h>
#include <Include/MovementComponent.h>
#include <Include/AttributeComponent.h>
#include <Include/ShootComponent.h>
#include <Include/Bullet.h>
#include <Include/Effect.h>

class Actor : public Unit
{
protected:
	sf::Color baseFillColor;
	float baseRadius;
	sf::Vector2f baseOrigin;
	sf::Vector2f baseScale;
	size_t basePointCount;

	sf::RectangleShape collisionCheckers[4];

	MovementComponent* movementComponent;
	AttributeComponent* attributeComponent;
	ShootComponent* shootComponent;
public:
	Actor();
	virtual ~Actor();
	
	virtual const bool completelyIntersects(const sf::FloatRect bounds) const;
	virtual const unsigned char getSideOfCollision(const sf::FloatRect bounds) const;

	virtual void createMovementComponent(const float max_velocity, const float acceleration, const float deceleration);
	virtual void createAttributeComponent(const unsigned level);
	virtual void createShootComponent();

	virtual void resetHP();
	virtual void loseHP(const int hp);
	virtual void gainHP(const int hp);
	virtual void loseEXP(const int exp);
	virtual void gainEXP(const int exp);
	virtual const bool isDead() const;
	virtual const int getLevel() const;
	virtual const int getHP() const;
	virtual const int getHPMax() const;
	virtual const int getEXP() const;
	virtual const long getEXPNext() const;
	virtual const float getReloadTime() const;
	virtual const float getReloadTimer() const;
	virtual const bool selectAttributePoints(const int& choise);
	virtual void levelUp();
	virtual void debugPrint();

	virtual void move(float dir_x, float dir_y, const float& dt);
	virtual void setMaxVelocity(float max_velocity);
	virtual void resetMaxVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();

	virtual void shoot(Unit* caster, std::list<Bullet*>* bullets);
	virtual void pick();
	virtual void dash();

	virtual void explode(std::list<Effect*>* effects);
	virtual void blink(std::list<Effect*>* effects);

 	virtual void update(const float& dt, const sf::Vector2f& target_position) = 0;
	virtual void updateAutoShooting(Unit* caster, std::list<Bullet*>* bullets) = 0;
	
 	virtual void updateCollisionCheckers();
 	virtual void renderCollisionCheckers(sf::RenderTarget* target = nullptr);
};

#include <Source/Actor.cpp>
#endif
