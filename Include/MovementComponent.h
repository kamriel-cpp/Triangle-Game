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
	~MovementComponent();

	void initVariables(sf::Shape* shape,
		float maxVelocity, float accelererion, float deceleration);
	const float& getMaxVelocity() const;
	const sf::Vector2f& getVelocity() const;
	const bool getState(const unsigned char state) const;
	void resetVelocity();

	void move(const float dir_x, const float dir_y, const float& dt);
	void update(const float& dt);
};

#include <Source/MovementComponent.cpp>
#endif
