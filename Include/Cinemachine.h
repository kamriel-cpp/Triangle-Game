#ifndef CINEMACHINE_H
#define CINEMACHINE_H

class Cinemachine
{
private:
	Camera* camera;
	sf::Shape* target;
	float damping;
	sf::Vector2f deadZone;
public:
	Cinemachine();
	virtual ~Cinemachine();

	void setCamera (Camera* camera);
	void setTarget (sf::Shape* target);
	void setDamping(float damping);
	void setDeadZone(const sf::Vector2f& dead_zone);
	void setDeadZone(float dead_zone_x, float dead_zone_y);

	void update(const float& dt);
};

#include <Source/Cinemachine.cpp>
#endif
