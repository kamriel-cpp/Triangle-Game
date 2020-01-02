#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

class MovementComponent
{
private:
	sf::Shape* shape;
	float maxVelocity;
	float acceleration;
	float deceleration;
	sf::Vector2f velocity;
public:
	MovementComponent();
	MovementComponent(sf::Shape* shape,
		float maxVelocity, float accelererion, float deceleration);
	virtual ~MovementComponent();

	void initVariables(sf::Shape* shape,
		float maxVelocity, float accelererion, float deceleration);
	const float& getMaxVelocity() const;
	const sf::Vector2f& getVelocity() const;
	const bool getState(const unsigned char state) const;
	void resetVelocityX();
	void resetVelocityY();

	void move(float dir_x, float dir_y, const float& dt);
	void update(const float& dt);
};

#include <Source/MovementComponent.cpp>
#endif
