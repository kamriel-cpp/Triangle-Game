#ifndef ACTOR_H
#define ACTOR_H
#include <Include/Bullet.h>
#include <Include/Effect.h>

class Actor : public sf::CircleShape
{
protected:
	sf::Color defaultColor;
	float defaultRadius;
	sf::Vector2f defaultOrigin;
	sf::Vector2f defaultScale;
	size_t defaultPointCount;
	float defaultMaxVelocity;

	sf::RectangleShape collisionCheckers[4];

	MovementComponent* movementComponent;
	AttributeComponent* attributeComponent;
	AttackComponent* attackComponent;
public:
	Actor();
	virtual ~Actor();
	
	virtual const bool completelyIntersects(const sf::FloatRect bounds) const;
	virtual const unsigned char getSideOfCollision(const sf::FloatRect bounds) const;

	virtual void createMovementComponent(const float max_velocity, const float acceleration, const float deceleration);
	virtual void createAttributeComponent(const unsigned level);
	virtual void createAttackComponent(const bool can_shoot, const bool can_pick, const bool can_dash,
		const float& shooting_cooldown, const float& picking_cooldown, const float& dashing_cooldown, float damage);

	virtual void loseHP(const int hp);
	virtual void gainHP(const int hp);
	virtual void loseEXP(const int exp);
	virtual void gainEXP(const int exp);
	virtual const bool isDead() const;

	virtual void move(float dir_x, float dir_y, const float& dt);
	virtual void setMaxVelocity(float max_velocity);
	virtual void resetMaxVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();

	virtual void shoot(std::list<Bullet*>* bullets);
	virtual void pick();
	virtual void dash();

	virtual void explode(std::list<Effect*>* effects);
	virtual void blink(std::list<Effect*>* effects);

 	virtual void update(const float& dt, const sf::Vector2f& target_position) = 0;
 	void updateCollisionCheckers();
};

#include <Source/Actor.cpp>
#endif
