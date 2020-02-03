#ifndef PARTICLE_H
#define PARTICLE_H

class Particle : public sf::CircleShape
{
public:
	int fadingSpeed;
	float movingSpeed;
public:
	Particle(const sf::Vector2f& position, sf::Color color,
		const float& radius, const float& points_count, const float& angle,
		const int& fading_speed, const float& moving_speed);
	virtual ~Particle();
	
 	void update(const float& dt);
};

#include <Source/Particle.cpp>
#endif
