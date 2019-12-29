#ifndef CINEMACHINE_H
#define CINEMACHINE_H

class Cinemachine
{
private:
	Camera* camera;
	sf::Shape* target;
public:
	Cinemachine();
	virtual ~Cinemachine();

	void setCamera (Camera* camera);
	void setTarget (sf::Shape* target);

	void update(const float& dt);
};

#include <Source/Cinemachine.cpp>
#endif
