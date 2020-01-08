#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle
{
protected:
	sf::Color defaultColor;
	float defaultRadius;
	sf::Vector2f defaultOrigin;
	sf::Vector2f defaultScale;
	size_t defaultPointCount;
	float defaultMaxVelocity;

	MovementComponent* movementComponent;
	AttributeComponent* attributeComponent;

	sf::RectangleShape collisionCheckers[4];
public:
	sf::CircleShape shape;
 	bool collision;
public:
 	Triangle();
 	virtual ~Triangle();

	void createMovementComponent(const float max_velocity, const float acceleration, const float deceleration);
	void createAttributeComponent(const unsigned level);

	void loseHP(const int hp);
	void gainHP(const int hp);
	void loseEXP(const int exp);
	void gainEXP(const int exp);

	void move(float dir_x, float dir_y, const float& dt);
	void move(float offsetX, float offsetY);
	void move(const sf::Vector2f& offset);

	void setMaxVelocity(float max_velocity);
	void resetMaxVelocity();
	void resetVelocityX();
	void resetVelocityY();

	virtual const bool intersects(const sf::FloatRect bounds) const;
	virtual const unsigned char getSideOfCollision(const sf::FloatRect bounds) const;

 	virtual void update(const float& dt, const sf::Vector2f& target_position) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#include <Source/Triangle.cpp>
#endif
