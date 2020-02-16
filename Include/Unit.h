#ifndef UNIT_H
#define UNIT_H

#include <Include/MovementComponent.h>
#include <Include/AttributeComponent.h>
#include <Include/ShootComponent.h>
#include <Include/Bullet.h>
#include <Include/Effect.h>

class Unit : public sf::CircleShape
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
	Unit();
	virtual ~Unit();
	
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
	
	virtual const bool wasChangedLVL() const;
	virtual const bool wasChangedEXP() const;
	virtual const bool wasChangedAPS() const;
	virtual const bool wasChangedHP() const;

	virtual const int getAttribute(const unsigned int attribute_tag) const;
	virtual const int getLVL() const;
	virtual const int getEXP() const;
	virtual const long getEXPNext() const;
	virtual const int getAPS() const;
	virtual const int getHP() const;
	virtual const float getReloadPercent() const;
	virtual const bool manualDistributeAPS(const int& choise);
	virtual void lvlUp();
	virtual void debugStatsPrint();

	virtual void move(float dir_x, float dir_y, const float& dt);
	virtual void setMaxVelocity(float max_velocity);
	virtual void resetMaxVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();

	virtual void shoot(std::list<Bullet*>* bullets);

	virtual void explode(std::list<Effect*>* effects);
	virtual void blink(std::list<Effect*>* effects);

	virtual void updateAutoShooting(std::list<Bullet*>* bullets);
	virtual void updateTrackingLook(const sf::Vector2f& target_position);
	virtual void updateTrackingMove(const sf::Vector2f& target_position, const float& dt);
	virtual void updateComponents(const float& dt);
 	virtual void update(std::list<Bullet*>* bullets, const sf::Vector2f& target_position, const float& dt) = 0;
	
 	virtual void updateCollisionCheckers();
 	virtual void renderCollisionCheckers(sf::RenderTarget* target = nullptr);
};

#include <Source/Unit.cpp>
#endif
