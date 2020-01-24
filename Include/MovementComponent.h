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

	const sf::Vector2f& getVelocity() const;
	const float& getMaxVelocity() const;
	const bool getState(const unsigned char state) const;

	void setMaxVelocity(float max_velocity);
	void stopVelocityX();
	void stopVelocityY();

	void move(float dir_x, float dir_y, const float& dt);
	void update(const float& dt);
};

#include <Source/MovementComponent.cpp>
#endif
